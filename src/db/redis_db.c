#include <db/redis_db.h>

#include <asm-generic/errno.h>
#include <bits/types/struct_timeval.h>
#include <time.h>
#include <errno.h>
#include <hiredis/read.h>
#include <stdint.h>
#include <stdlib.h>
#include <hiredis/hiredis.h>
#include <string.h>

#ifdef CURL_GTEST
extern redisReply _GTEST_REDIS_REPLY_VALUE;
extern redisReply _GTEST_REDIS_REPLY_TS;
extern redisReply _GTEST_REDIS_STORE_REPLY;
extern char *_GTEST_REDIS_STORE_VALUE;
extern char *_GTEST_REDIS_STORE_TS;
extern redisContext *_GTEST_REDIS_CONTEX;
#endif /* ifdef CURL_GTEST */

redisContext *global_redis_database = NULL;
redisContext *db_init(const char *hostname, uint32_t port)
{
    redisContext *ret = NULL;
    redisContext *c;
    if (hostname == NULL) {
        errno = EINVAL;
        goto end;
    }
    if (port == 0) {
        errno = EINVAL;
        goto end;
    }
    struct timeval timeout = { 1, 500000 };
#ifdef CURL_GTEST
    c = _GTEST_REDIS_CONTEX;
#else
    c = redisConnectWithTimeout(hostname, port, timeout);
#endif /* if CURL_GTEST */

    if (c == NULL) {
        printf("Connection error: can't allocate redis context\n");
        errno = ENOMEM;
        goto end;
    }

    if (c->err) {
        printf("Connection error: %s\n", c->errstr);
#ifndef CURL_GTEST
        redisFree(c);
#endif /* if CURL_GTEST */
        errno = ECONNREFUSED;
        goto end;
    }

    ret = c;

end:
    return ret;
}

/** @brief request single value from key string
 *
 *  @paran context the database context
 *  @paran string the key to find in the database
 *  @return returns the value matiching the string
 * */
static const char *db_request_string(redisContext *context, const char *string)
{
    char *ret = NULL;
    redisReply *reply = NULL;

#ifdef CURL_GTEST
    if (strstr(string, "_ts")) {
        reply = &_GTEST_REDIS_REPLY_TS;
    } else {
        reply = &_GTEST_REDIS_REPLY_VALUE;
    }
#else
    reply = redisCommand(context, "GET %s", string);
#endif /* ifdef CURL_GTEST */

    if (reply->type != REDIS_REPLY_STRING) {
        errno = EMEDIUMTYPE;
        goto redis_free;
    }
    size_t reply_size = strlen(reply->str);
    ret = malloc(reply_size);

    if (ret == NULL) {
        errno = ENOMEM;
        goto redis_free;
    }

    memcpy(ret, reply->str, reply_size);

redis_free:
#ifndef CURL_GTEST
    freeReplyObject(reply);
#endif /* ifdef CURL_GTEST */

    return ret;
}

const char *db_lookup(redisContext *context, const char *hash,
                      struct timespec *ts)
{
    const char *ret = NULL;
    const char *ts_str = NULL;

    if (context == NULL || hash == NULL || ts == NULL) {
        errno = EINVAL;
        goto end;
    }
    ret = db_request_string(context, hash);
    if (ret == NULL)
        goto end;

    char *hash_ts = malloc(strlen(hash) + 4);
    snprintf(hash_ts, strlen(hash) + 4, "%s_ts", hash);

    ts_str = db_request_string(context, hash_ts);
    if (ts_str == NULL)
        goto free_hash_ts;

    memset(ts, 0, sizeof(struct timespec));

    ts->tv_sec = atoi(ts_str);

    free(ts_str);
free_hash_ts:
    free(hash_ts);
end:
    return ret;
}

/** @brief store single key-value pair
 *
 *  @paran context the database context
 *  @paran key the key to store the value in the database
 *  @paran value the value to store in the database
 * */
static void db_store_string(redisContext *context, const char *key,
                            const char *value)
{
    redisReply *reply;
#ifdef CURL_GTEST
    if (strstr(key, "_ts")) {
        _GTEST_REDIS_STORE_TS = malloc(strlen(value) + 4);
        strcpy(_GTEST_REDIS_STORE_TS, value);
        reply = &_GTEST_REDIS_STORE_REPLY;
    } else {
        _GTEST_REDIS_STORE_VALUE = malloc(strlen(value) + 4);
        strcpy(_GTEST_REDIS_STORE_VALUE, value);
        reply = &_GTEST_REDIS_STORE_REPLY;
    }
#else
    reply = redisCommand(context, "SET %s %s", key, value);
#endif

    if (reply->type == REDIS_REPLY_ERROR)
        errno = EMEDIUMTYPE;

#ifndef CURL_GTEST
    freeReplyObject(reply);
#endif
    return;
}

void db_store(redisContext *context, const char *key, const char *value)
{
    char key_buffer[128];
    char ts_buffer[128];
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);

    if (context == NULL || key == NULL || value == NULL) {
        errno = EINVAL;
        goto end;
    }
    db_store_string(context, key, value);

    snprintf(key_buffer, 127, "%s_ts", key);
    snprintf(ts_buffer, 127, "%ld", ts.tv_sec);

    db_store_string(context, key_buffer, ts_buffer);

end:
    return;
}

void db_stop(redisContext *context)
{
    redisFree(context);
}
