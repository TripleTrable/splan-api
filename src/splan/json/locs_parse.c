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

loc *locs_parse_json(const char *data)
{
    loc *ret_val = NULL;
    printf("---------------\n");
    printf("%s", data);
    printf("---------------\n");
    cJSON *json = cJSON_Parse(data);

    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
            printf("===============\n");
            printf("%p\n", error_ptr);
            printf("%p\n", data);
            printf("===============\n");
        }
        errno = EINVAL;
        goto cleanup;
    }

    printf("===============\n");
    printf("%s\n", cJSON_Print(json));
    printf("===============\n");
    printf("%c\n", cJSON_IsArray(json));
    printf("===============\n");

cleanup:
    cJSON_Delete(json);
    return ret_val;
}
