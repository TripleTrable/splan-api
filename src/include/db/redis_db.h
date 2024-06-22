/*! @file  redis_db.h
 *  @brief Header file for the redis DB interactions
 *
 *  This file contains the functions to interact with the redis database.
 */
#ifndef DB_H
#define DB_H

#include <stdint.h>
#include <time.h>

typedef struct redisContext redisContext;

extern redisContext *
    global_redis_database; /*!< This is global struct to pass this data from the main.c file into the microhttpsd route context*/

/** @brief Initialize and connect to the redis DB
 *
 *  @param hostname the hostname of the database as a string
 *  @param port the port to connect to
 */
redisContext *db_init(const char *hostname, uint32_t port);

/** @brief lookup a cache entry in the database
 *
 *  @param context The database context from db_init
 *  @param hash    The hash to lookup as the key for the database
 *  @param ts      returns the timespec with only second of the time
 *                 of the creation of the database entry
 *
 *  @return The value of the data base entry for the hash
 */
const char *db_lookup(redisContext *context, const char *hash,
                      struct timespec *ts);

/** @brief store a key value pair inside the database
 *
 *  @param context The database context from db_init
 *  @param key     The key to store the value at
 *  @param value   The value to store in the database
 */
void db_store(redisContext *context, const char *key, const char *value);

/** @brief disconnect the database and free the context
 *
 *  @param context The database context from db_init
 */
void db_stop(redisContext *context);

#endif // !DB_H
