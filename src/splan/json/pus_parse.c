#include "splan/json/spapi.h"

#include "splan/spdata.h"
#include <asm-generic/errno-base.h>
#include <cjson/cJSON.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

pu *pus_parse_json(const char *_data)
{
    pu *ret_val = NULL;

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
    ret_val = (pu *)calloc(size, sizeof(pu));
    pu *iterator = ret_val;
    cJSON_ArrayForEach(child, data)
    {
        cJSON *tmp = cJSON_GetObjectItem(child, "id");
        if (tmp == NULL || !cJSON_IsNumber(tmp)) {
            free(ret_val);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        iterator->id = tmp->valueint;

        tmp = cJSON_GetObjectItem(child, "shortname");
        if (tmp == NULL || !cJSON_IsString(tmp)) {
            pu_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        iterator->shortname =
            calloc(strlen(tmp->valuestring) + 1, sizeof(char));
        if (!iterator->shortname) {
            pu_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        strcpy(iterator->shortname, tmp->valuestring);

        tmp = cJSON_GetObjectItem(child, "name");
        if (tmp == NULL || !cJSON_IsString(tmp)) {
            pu_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        iterator->name = calloc(strlen(tmp->valuestring) + 1, sizeof(char));
        if (!iterator->name) {
            pu_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        strcpy(iterator->name, tmp->valuestring);

        tmp = cJSON_GetObjectItem(child, "startdate");
        if (tmp == NULL || !cJSON_IsString(tmp)) {
            pu_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        iterator->startdate =
            calloc(strlen(tmp->valuestring) + 1, sizeof(char));
        if (!iterator->name) {
            pu_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        strcpy(iterator->startdate, tmp->valuestring);

        tmp = cJSON_GetObjectItem(child, "enddate");
        if (tmp == NULL || !cJSON_IsString(tmp)) {
            pu_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        iterator->enddate = calloc(strlen(tmp->valuestring) + 1, sizeof(char));
        if (!iterator->name) {
            pu_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        strcpy(iterator->enddate, tmp->valuestring);

        tmp = cJSON_GetObjectItem(child, "dateasdefault");
        if (tmp == NULL || !cJSON_IsBool(tmp)) {
            pu_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        iterator->dateasdefault = (uint8_t)tmp->valueint;

        //TODO: Parse defaultloc correct
        iterator->defaultloc = NULL;

        tmp = cJSON_GetObjectItem(child, "visibleonweb");
        if (tmp == NULL || !cJSON_IsBool(tmp)) {
            pu_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        iterator->visibleonweb = (uint8_t)tmp->valueint;

        iterator++;
    }

cleanup:
    cJSON_Delete((void *)json);
    return ret_val;
}
