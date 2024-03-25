#include "spapi.h"

#include <cjson/cJSON.h>
#include <stdio.h>
#include <errno.h>

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
    cJSON *json = cJSON_Parse(_data);

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
    cJSON *data = json->child->child;

    printf("===============\n");
    printf("%s\n", cJSON_Print(data));
    printf("===============\n");
    printf("%s\n", cJSON_Print(data->next));
    printf("===============\n");

cleanup:
    cJSON_Delete(json);
    return ret_val;
}
