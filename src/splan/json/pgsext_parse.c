#include "splan/json/spapi.h"

#include "splan/spdata.h"
#include <asm-generic/errno-base.h>
#include <cjson/cJSON.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

/*

   [
  [
    {
      "id": 14119,
      "shortname": "INF-M/FWPM",
      "name": "Masterstudiengang Informatik - fachwissenschaftliche Wahlpflichtmodule",
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
    },
    {
      "id": 13815,
      "shortname": "INF-M/Pflicht",
      "name": "Masterstudiengang Informatik - Pflichtmodule",
      "lectures": [
        {
          "id": 3210,
          "shortname": "Fachschaft INF",
          "name": "Fachschaft INF",
          "pgid": 13796
        },
        {
          "id": 1072,
          "shortname": "MVI",
          "name": "Mathematische Verfahren der Informatik",
          "pgid": 13815
        },
      ]
    }
  ]
]

 */

pgsext *pgsext_parse_json(const char *_data)
{
    pgsext *ret_val = NULL;

    if (_data == NULL) {
        errno = EINVAL;
        return NULL;
    }

    const cJSON *json = cJSON_Parse(_data);

    printf("BEGIN\n%s\nEND\n", cJSON_Print(json));
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
    ret_val = (pgsext *)calloc(size, sizeof(pgsext));
    pgsext *iterator = ret_val;
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
            pgsext_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        iterator->shortname =
            calloc(strlen(tmp->valuestring) + 1, sizeof(char));
        if (!iterator->shortname) {
            pgsext_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        strcpy(iterator->shortname, tmp->valuestring);

        tmp = cJSON_GetObjectItem(child, "name");
        if (tmp == NULL || !cJSON_IsString(tmp)) {
            pgsext_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        iterator->name = calloc(strlen(tmp->valuestring) + 1, sizeof(char));
        if (!iterator->name) {
            pgsext_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        strcpy(iterator->name, tmp->valuestring);

        tmp = cJSON_GetObjectItem(child, "lectures");
        if (tmp == NULL || !cJSON_IsArray(tmp)) {
            pgsext_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }

        size_t lec_size;
        lecture *lectures = lecture_parse(tmp, &lec_size);
        if (!lectures) {
            lecture_free_all(lectures, lec_size);
            pgsext_free_all(ret_val, size);
            ret_val = NULL;
            errno = EINVAL;
            goto cleanup;
        }
        iterator->lectures = lectures;
        iterator->lecture_count = lec_size;

        iterator++;
    }

cleanup:
    cJSON_Delete(json);
    return ret_val;
}
