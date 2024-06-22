/*! @file  sha256_string.h
 *  @brief Header file for the sha256_string function
 *
 *  This file contains the function declaration for the sha256_string function
 */

#ifndef SHA256_SRTING
#define SHA256_SRTING

/** @brief Genreates a SHA256 hash from a string
 *
 *  @param string String to shash
 *  @param outputBuffer 65 byte large buffer which is filled with the hash
 * */
void sha256_string(const char *string, char outputBuffer[65]);

#endif // !SHA256_SRTING
