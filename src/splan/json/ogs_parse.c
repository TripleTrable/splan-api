#include "splan/json/spapi.h"

#include "splan/spdata.h"
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
      "id": 105,
      "shortname": "AAI-B",
      "name": "Bachelorstudiengang Applied Artificial Intelligence"
    },
    {
      "id": 41,
      "shortname": "AFE-M",
      "name": "Masterstudiengang Angewandte Forschung & Entwicklung in den Ingenieurwissenschaften"
    },
  ]
]
 */

og *ogs_parse_json(const char *_data)
{
    og *ret_val = NULL;

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
        return NULL;
    }

    // can use hard coding to access this as the double array is always present
    //
    const cJSON *data = json->child;

    const cJSON *child;

    size_t size = cJSON_GetArraySize(data);
    ret_val = (og *)calloc(size, sizeof(og));
    og *iterator = ret_val;
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
            og_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        iterator->shortname =
            calloc(strlen(tmp->valuestring) + 1, sizeof(char));
        if (!iterator->shortname) {
            og_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        strcpy(iterator->shortname, tmp->valuestring);

        tmp = cJSON_GetObjectItem(child, "name");
        if (tmp == NULL || !cJSON_IsString(tmp)) {
            og_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        iterator->name = calloc(strlen(tmp->valuestring) + 1, sizeof(char));
        if (!iterator->name) {
            og_free_all(ret_val, size);
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
