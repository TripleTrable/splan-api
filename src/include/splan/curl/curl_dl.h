/*! @file  curl_dl.h
 *  @brief Header file for the curl_dl handler
 *
 *  This file contains the function declarations for the curl http-get request handler
 */

#ifndef CURL_DL_H
#define CURL_DL_H

/** @brief Make a curl get request to the uri
 *
 *  @param url url to call
 *  @return returns the content of the request as a string
 * */
const char *curl_get(const char *url);

#endif // !CURL_DL_H
