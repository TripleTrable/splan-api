#include "splan/json/spapi.h"
#include "splan/curl/curl_dl.h"

#include "splan/spdata.h"
#include <asm-generic/errno-base.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

loc *splan_get_locs(void)
{
    size_t url_len;
    char *url;

    if (_server_config.server_api_endpoint == NULL) {
        errno = EINVAL;
        return NULL;
    }
    url_len = strlen(_server_config.server_api_endpoint) + 512;
    url = malloc(url_len);

    snprintf(url, url_len, "%s?m=getlocs", _server_config.server_api_endpoint);
    printf("URL: %s\n", url);

    const char *data = curl_get(url);
    free(url);

    char *utf8_response = iso8859_1_to_utf_8(data);

    free((void *)data);
    loc *locs = locs_parse_json(utf8_response);

    free(utf8_response);

    return locs;
}

char *splan_get_locs_json(void)
{
    size_t url_len;
    char *url;

    if (_server_config.server_api_endpoint == NULL) {
        errno = EINVAL;
        return NULL;
    }
    url_len = strlen(_server_config.server_api_endpoint) + 512;
    url = malloc(url_len);

    snprintf(url, url_len, "%s?m=getlocs", _server_config.server_api_endpoint);
    printf("URL: %s\n", url);

    const char *data = curl_get(url);
    free(url);

    char *utf8_response = iso8859_1_to_utf_8(data);

    return utf8_response;
}
