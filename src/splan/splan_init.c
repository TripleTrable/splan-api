#include "spdata.h"
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

server_user_config _server_config;
int splan_init(server_user_config *config)
{
	int endpoint_length = strlen(config->server_api_endpoint) + 1;

	_server_config.server_api_endpoint = malloc(endpoint_length);
	if (_server_config.server_api_endpoint == NULL) {
		perror("Could not allocate memory for the api_endpoint string\n");
		return -1;
	}
	strncpy(_server_config.server_api_endpoint, config->server_api_endpoint,
		endpoint_length);

	curl_global_init(CURL_GLOBAL_ALL);
	return 0;
}
