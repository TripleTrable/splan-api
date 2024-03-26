#include "splan/spdata.h"
#include <asm-generic/errno-base.h>
#include <curl/curl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

server_user_config _server_config;
int splan_init(server_user_config *config)
{
    if (!config || !config->server_api_endpoint) {
        errno = EINVAL;
        return -1;
    }
    int endpoint_length = strlen(config->server_api_endpoint) + 1;

    _server_config.server_api_endpoint = calloc(endpoint_length, sizeof(char));
    if (_server_config.server_api_endpoint == NULL) {
        perror("Could not allocate memory for the api_endpoint string\n");
        return -1;
    }
    strncpy(_server_config.server_api_endpoint, config->server_api_endpoint,
            endpoint_length);
    _server_config.server_api_endpoint[endpoint_length - 1] = '\0';

    curl_global_init(CURL_GLOBAL_ALL);
    return 0;
}
