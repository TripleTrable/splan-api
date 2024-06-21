#include <curl/curl.h>
#include <gtest/gtest.h>
#include <hiredis/read.h>
#include <sys/mman.h>

extern "C" {
#include <db/redis_db.h>
#include <errno.h>
#include <hiredis/hiredis.h>
#include <sha256_string.h>
#include <string.h>

redisReply _GTEST_REDIS_REPLY_VALUE;
redisReply _GTEST_REDIS_REPLY_TS;
char *_GTEST_REDIS_STORE_VALUE;
char *_GTEST_REDIS_STORE_TS;
redisReply _GTEST_REDIS_STORE_REPLY;
redisContext *_GTEST_REDIS_CONTEX;

typedef struct {
  uint8_t *memory;
  size_t size;
} response_memory;
}

TEST(redis_lookup, Correct) {
  int dummy;
  redisContext *context = (redisContext *)((
      void *)&dummy); // as this is mocked it is possible to be non valid
                      // pointer magic for a valid non null context pointer
  const char *hash = "DISREGARD"; // disregared as the mock always works
  char *value = "hello world";

  struct timespec ts;
  timespec_get(&ts, TIME_UTC);
  char ts_str[128];
  snprintf(ts_str, 127, "%ld", ts.tv_sec);

  _GTEST_REDIS_REPLY_TS.str = ts_str;
  _GTEST_REDIS_REPLY_TS.type = REDIS_REPLY_STRING;
  _GTEST_REDIS_REPLY_VALUE.str = value;
  _GTEST_REDIS_REPLY_VALUE.type = REDIS_REPLY_STRING;

  const char *reply = NULL;
  struct timespec ts_reply;

  reply = db_lookup(context, hash, &ts_reply);

  ASSERT_STREQ(reply, value);
  ASSERT_EQ(ts_reply.tv_sec, ts.tv_sec);
}

TEST(redis_lookup, null_key) {
  int dummy;
  redisContext *context = (redisContext *)((
      void *)&dummy); // as this is mocked it is possible to be non valid
                      // pointer magic for a valid non null context pointer
  const char *hash = NULL;

  const char *reply = NULL;
  struct timespec ts_reply;

  reply = db_lookup(context, hash, &ts_reply);

  ASSERT_TRUE(reply == NULL);
  ASSERT_TRUE(errno == EINVAL);
}

TEST(redis_lookup, null_ts) {
  int dummy;
  redisContext *context = (redisContext *)((
      void *)&dummy); // as this is mocked it is possible to be non valid
                      // pointer magic for a valid non null context pointer
  const char *hash = "key";

  const char *reply = NULL;

  reply = db_lookup(context, hash, NULL);

  ASSERT_TRUE(reply == nullptr);
  ASSERT_TRUE(errno == EINVAL);
}

TEST(redis_store, Correct) {
  int dummy;
  redisContext *context = (redisContext *)((
      void *)&dummy); // as this is mocked it is possible to be non valid
                      // pointer magic for a valid non null context pointer
  const char *hash = "DISREGARD"; // disregared as the mock always works
  const char *value = "hello world";

  struct timespec before;
  struct timespec after;
  timespec_get(&before, TIME_UTC);

  _GTEST_REDIS_STORE_REPLY.type = REDIS_REPLY_STRING;

  db_store(context, hash, value);

  timespec_get(&after, TIME_UTC);

  ASSERT_STREQ(value, _GTEST_REDIS_STORE_VALUE);
  uint64_t time_s = atoll(_GTEST_REDIS_STORE_TS);

  printf("%s == %ld", _GTEST_REDIS_STORE_TS, time_s);

  ASSERT_GE(time_s, before.tv_sec);
  ASSERT_LE(time_s, after.tv_sec);
}

TEST(redis_store, null_key) {
  int dummy;
  redisContext *context = (redisContext *)((
      void *)&dummy); // as this is mocked it is possible to be non valid
                      // pointer magic for a valid non null context pointer
  const char *key = NULL;
  const char *value = "Hello World";

  db_store(context, key, value);
  ASSERT_TRUE(errno == EINVAL);
}

TEST(redis_store, null_value) {
  int dummy;
  redisContext *context = (redisContext *)((
      void *)&dummy); // as this is mocked it is possible to be non valid
                      // pointer magic for a valid non null context pointer
  const char *key = "Hello World";
  const char *value = NULL;

  db_store(context, key, value);
  ASSERT_TRUE(errno == EINVAL);
}

TEST(redis_store, null_context) {
  redisContext *context = NULL;
  const char *key = "Hello World";
  const char *value = "foo bare";

  db_store(context, key, value);
  ASSERT_TRUE(errno == EINVAL);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
