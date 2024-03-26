#include "splan/json/spapi.h"

#include <asm-generic/errno-base.h>
#include <cjson/cJSON.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

/*
 * [
  [
    {
      "id": 3,
      "shortname": "*RO",
      "name": "Rosenheim (Hochschule)"
    },
    {
      "id": 6,
      "shortname": "AÖ",
      "name": "Altötting (Berufliche Oberschule Inn-Salzach)"
    },
  ]
]
 */

loc *locs_parse_json(const char *_data)
{
    loc *ret_val = NULL;

    if (_data == NULL) {
        errno = EINVAL;
        return NULL;
    }

    const cJSON *json = cJSON_Parse(_data);

    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        errno = EINVAL;
        goto cleanup;
    }

    // can use hard coding to access this as the double array is always present
    //
    const cJSON *data = json->child;

    const cJSON *child;

    size_t size = cJSON_GetArraySize(data);
    ret_val = (loc *)malloc(size * sizeof(loc));
    loc *iterator = ret_val;
    cJSON_ArrayForEach(child, data)
    {
        const cJSON *tmp = cJSON_GetObjectItem(child, "id");
        if (tmp == NULL || !cJSON_IsNumber(tmp)) {
            free(ret_val);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        iterator->id = tmp->valueint;

        tmp = cJSON_GetObjectItem(child, "shortname");
        if (tmp == NULL || !cJSON_IsString(tmp)) {
            free(ret_val);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        iterator->shortname =
            calloc(strlen(tmp->valuestring) + 1, sizeof(char));
        if (!iterator->shortname) {
            free(ret_val);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        strcpy(iterator->shortname, tmp->valuestring);

        tmp = cJSON_GetObjectItem(child, "name");
        if (tmp == NULL || !cJSON_IsString(tmp)) {
            free(iterator->shortname);
            free(ret_val);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        iterator->name = calloc(strlen(tmp->valuestring) + 1, sizeof(char));
        if (!iterator->name) {
            free(iterator->shortname);
            free(ret_val);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        strcpy(iterator->name, tmp->valuestring);

        iterator++;
    }

cleanup:
    cJSON_Delete(json);
    return ret_val;
}
