#include "splan/json/spapi.h"

#include "splan/spdata.h"
#include <asm-generic/errno-base.h>
#include <cjson/cJSON.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

/*
      "lectures": [
        {
          "id": 4721,
          "shortname": "DL",
          "name": "Deep Learning",
          "pgid": 14119
        },
        {
          "id": 4166,
          "shortname": "DSP",
          "name": "Digital Signal Processing and Machine Learning",
          "pgid": 14119
        },
      ]
 */

lecture *lecture_parse(const cJSON *_data, size_t *_size)
{
    lecture *ret_val = NULL;

    printf("BEGIN\n%s\nEND\n", cJSON_Print(_data));
    *_size = 0;
    if (_data == NULL) {
        errno = EINVAL;
        return NULL;
    }

    const cJSON *child;

    size_t size = cJSON_GetArraySize(_data);
    ret_val = (lecture *)calloc(size, sizeof(lecture));
    lecture *iterator = ret_val;
    cJSON_ArrayForEach(child, _data)
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
            lecture_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        iterator->shortname =
            calloc(strlen(tmp->valuestring) + 1, sizeof(char));
        if (!iterator->shortname) {
            lecture_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        strcpy(iterator->shortname, tmp->valuestring);

        tmp = cJSON_GetObjectItem(child, "name");
        if (tmp == NULL || !cJSON_IsString(tmp)) {
            lecture_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        iterator->name = calloc(strlen(tmp->valuestring) + 1, sizeof(char));
        if (!iterator->name) {
            lecture_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        strcpy(iterator->name, tmp->valuestring);

        tmp = cJSON_GetObjectItem(child, "pgid");
        if (tmp == NULL || !cJSON_IsNumber(tmp)) {
            lecture_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        iterator->pgid = (uint64_t)tmp->valueint;

        iterator++;
    }

    *_size = size;
cleanup:
    return ret_val;
}
