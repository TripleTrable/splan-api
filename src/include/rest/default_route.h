#ifndef DEFAULT_ROUTE_H
#define DEFAULT_ROUTE_H

#include <microhttpd.h>

enum MHD_Result default_handler(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls);

typedef enum {
    HTTP_OK = 200,
    HTTP_BAD_REQUEST = 400,
    HTTP_NOT_FOUND = 404,
    HTTP_INTERNAL_SERVER_ERROR = 500,
    HTTP_NOT_IMPLEMENTED = 501
} HTTP_status;

typedef struct {
    char *body;
    HTTP_status status;
} HTTP_response;

#endif /* ifndef DEFAULT_ROUTE_H */
