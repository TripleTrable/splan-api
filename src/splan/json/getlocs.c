#include "splan/json/spapi.h"
#define CURL_ICONV_CODESET_OF_NETWORK "ISO8859-1"

#define CURL_ICONV_CODESET_FOR_UTF8 "UTF-8"
#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct {
    uint8_t *memory;
    size_t size;
} response_memory;

size_t write_callback(void *contents, size_t size, size_t nmemb,
                             void *usrptr)
{
    size_t realsize = size * nmemb; // size is always 3
    response_memory *mem = (response_memory *)usrptr;

    uint8_t *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        perror("Could not allocate memory during curl callback");
        return 0;
    }
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

loc *splan_get_locs(void)
{
    CURL *curl;
    CURLcode res;
    size_t url_len;
    char *url;
    response_memory chunk;
    loc *ret_val = NULL;
    struct curl_slist *headers = NULL;

    chunk.memory = malloc(1);
    chunk.size = 0;

    curl = curl_easy_init();
    if (!curl)
        return NULL;

    url_len = strlen(_server_config.server_api_endpoint) + 11;
    url = malloc(url_len);

    snprintf(url, url_len, "%s?m=getlocs", _server_config.server_api_endpoint);
    printf("URL: %s\n", url);

    // set  url
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // set callback for writing
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    // set memory location for write callback (4th parameter)
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    /* some servers do not like requests that are made without a user-agent
     field, so we provide one */
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    headers = curl_slist_append(
        headers, "Content-Type: application/json;charset=ISO-8859-1");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    res = curl_easy_perform(curl);

#ifdef CURL_GTEST
    // HERE we customize the result from curl to fit unit tests
    // TODO: make special gtest stuff here
#endif /* ifdef CURL_GTEST */

    if (res != CURLE_OK) {
        fprintf(stderr, "curle call failed: %s\n", curl_easy_strerror(res));
        goto cleanup;
    }

    char *utf8_response = iso8859_1_to_utf_8((char *)chunk.memory);
    ret_val = locs_parse_json(utf8_response);

    free(utf8_response);
cleanup:

    curl_easy_cleanup(curl);
    free(chunk.memory);

    return ret_val;
}
