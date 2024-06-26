#include "rest/default_route.h"
#include "splan/json/spapi.h"
#include <sha256_string.h>
#include <db/redis_db.h>
#include <time.h>
#include <memory.h>
#include <errno.h>
#include <microhttpd.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRY               \
    do {                  \
        jmp_buf ex_buf__; \
        if (!setjmp(ex_buf__)) {
#define CATCH \
    }         \
    else      \
    {
#define ETRY \
    }        \
    }        \
    while (0)

#define THROW(x) longjmp(ex_buf__, x)

struct MHD_Response *create_MHD_response(char *message)
{
    struct MHD_Response *response;

    if (message == NULL) {
        errno = EINVAL;
        return NULL;
    }

    response = MHD_create_response_from_buffer(strlen(message), (void *)message,
                                               MHD_RESPMEM_PERSISTENT);

    if (!response)
        return NULL;

    MHD_add_response_header(response, "Content-Type", "application/json");
    MHD_add_response_header(response, "Access-Control-Allow-Origin", "*");

    return response;
}

char *simple_message(const char *message)
{
    char *buffer = NULL;

    if (message == NULL) {
        errno = EINVAL;
        return NULL;
    }

    size_t size = strlen(message) + 20;
    buffer = (char *)malloc(size);

    if (buffer) {
        snprintf(buffer, size, "{\"message\": \"%s\"}", message);
    }

    return buffer;
}

/** @brief inline wrapper to simplify route validation
 * */
static inline int validate_route(const char *url, const char *path)
{
    return strstr(url, path) != NULL;
}

enum MHD_Result default_handler(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls)
{
    enum MHD_Result ret;

    struct MHD_Response *response;
    HTTP_response response_api;
    char sha256_buffer[65];
    memset(sha256_buffer, 0, 65);

    TRY
    {
        if (strcmp(url, "/health") == 0) {
            response_api =
                (HTTP_response){ .body = simple_message("Not implemented yet"),
                                 .status = HTTP_NOT_FOUND };
        }

        else if (validate_route(url, "/faculties")) {
            sha256_string(url, sha256_buffer);
            struct timespec cache_time;
            struct timespec now;
            timespec_get(&now, TIME_UTC);
            const char *c =
                db_lookup(global_redis_database, sha256_buffer, &cache_time);
            if (!c) {
                c = splan_get_locs_json();
                if (c == NULL)
                    THROW(1);
                db_store(global_redis_database, sha256_buffer, c);
            }
            if (now.tv_sec - cache_time.tv_sec > 500) {
                // cache is to old
                c = splan_get_locs_json();
                if (c == NULL)
                    THROW(1);
                db_store(global_redis_database, sha256_buffer, c);
            }
            response_api = (HTTP_response){ .body = c, .status = HTTP_OK };
        } else if (validate_route(url, "/timetable")) {
            response_api =
                (HTTP_response){ .body = simple_message("Not implemented yet"),
                                 .status = HTTP_NOT_FOUND };
        } else if (validate_route(url, "/semesters")) {
            sha256_string(url, sha256_buffer);
            struct timespec cache_time;
            struct timespec now;
            timespec_get(&now, TIME_UTC);
            const char *c =
                db_lookup(global_redis_database, sha256_buffer, &cache_time);

            if (!c) {
                c = splan_get_pus_json();
                if (c == NULL)
                    THROW(1);
                db_store(global_redis_database, sha256_buffer, c);
            }
            if (now.tv_sec - cache_time.tv_sec > 500) {
                // cache is to old
                c = splan_get_locs_json();
                if (c == NULL)
                    THROW(1);
                db_store(global_redis_database, sha256_buffer, c);
            }
            response_api = (HTTP_response){ .body = c, .status = HTTP_OK };
        }

        else {
            response_api =
                (HTTP_response){ .body = simple_message("404 Not found"),
                                 .status = HTTP_NOT_FOUND };
        }
    }
    CATCH
    {
        response_api =
            (HTTP_response){ .body = simple_message("Internal server error"),
                             .status = HTTP_INTERNAL_SERVER_ERROR };
    }
    ETRY;

    response = create_MHD_response(response_api.body);
    if (!response)
        return MHD_NO;

    ret = MHD_queue_response(connection, response_api.status, response);
    return ret;
}
