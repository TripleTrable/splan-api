#include "splan/curl/curl_dl.h"
#include "splan/spdata.h"
#include <curl/curl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CURL_ICONV_CODESET_OF_NETWORK "ISO8859-1"
#define CURL_ICONV_CODESET_FOR_UTF8 "UTF-8"
#ifdef CURL_GTEST
// HERE we customize the result from curl to fit unit tests
// TODO: make special gtest stuff here
extern int _GTEST_CURL_RESPONSE_MOC_RET;
extern uint8_t *_GTEST_CURL_RESPONSE_MEM;
extern int _GTEST_CURL_RESPONSE_MEM_SIZE;

#endif /* ifdef CURL_GTEST */

typedef struct {
    uint8_t *memory;
    size_t size;
} response_memory;

size_t write_callback(void *contents, size_t size, size_t nmemb, void *usrptr)
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

const char *curl_get(const char *url)
{
    CURL *curl = NULL;
    CURLcode res;
    response_memory chunk;
    char *content = NULL;
    struct curl_slist *headers = NULL;

    chunk.memory = malloc(1);
    chunk.size = 0;

    curl = curl_easy_init();
    if (!curl)
        goto cleanup;

    // set  url
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // set  url
    curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_3);

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
    // TODO: make special gtest stuff HERE
    res = _GTEST_CURL_RESPONSE_MOC_RET;
    chunk.memory = _GTEST_CURL_RESPONSE_MEM;
    chunk.size = _GTEST_CURL_RESPONSE_MEM_SIZE;
#endif /* ifdef CURL_GTEST */

    if (res != CURLE_OK) {
        fprintf(stderr, "curle call failed: %s\n", curl_easy_strerror(res));
        goto cleanup;
    }

    content = malloc(chunk.size);
    memcpy(content, chunk.memory, chunk.size);
cleanup:

    curl_easy_cleanup(curl);
#ifndef CURL_GTEST
    free(chunk.memory);
#endif /* ifndef  CURL_GTEST */

    return content;
}
