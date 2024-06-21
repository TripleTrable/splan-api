#ifndef DB_H
#define DB_H

#include <stdint.h>
#include <time.h>

typedef struct redisContext redisContext;

extern redisContext *global_redis_database;

redisContext *db_init(const char *hostname, uint32_t port);

const char *db_lookup(redisContext *context, const char *hash,
                      struct timespec *ts);

void db_store(redisContext *context, const char *key, const char *value);

void db_stop(redisContext *context);

#endif // !DB_H
