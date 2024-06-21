#include <cerrno>
#include <cstdlib>
#include <curl/curl.h>
#include <gtest/gtest.h>
#include <sys/mman.h>

extern "C" {
#include <db/redis_db.h>
#include <errno.h>
#include <hiredis/hiredis.h>
#include <string.h>

redisReply _GTEST_REDIS_REPLY_VALUE;
redisReply _GTEST_REDIS_REPLY_TS;
char *_GTEST_REDIS_STORE_VALUE;
char *_GTEST_REDIS_STORE_TS;
redisReply _GTEST_REDIS_STORE_REPLY;
redisContext *_GTEST_REDIS_CONTEX;
int _GTEST_CURL_RESPONSE_MOC_RET;
uint8_t *_GTEST_CURL_RESPONSE_MEM;
size_t _GTEST_CURL_RESPONSE_MEM_SIZE;

typedef struct {
  uint8_t *memory;
  size_t size;
} response_memory;
}

TEST(redisinit, Correct) {
  const char *hostname = "localhost";
  uint32_t port = 4177;
  _GTEST_REDIS_CONTEX = (redisContext *)malloc(sizeof(redisContext));

  printf("test\n");
  redisContext *context = db_init(hostname, port);
  printf("testr2\n");

  ASSERT_TRUE(context != nullptr);
  free(context);
}

TEST(redisinit, failed_context_alloc) {
  const char *hostname = "localhost";
  uint32_t port = 4177;
  _GTEST_REDIS_CONTEX = NULL;

  printf("test\n");
  redisContext *context = db_init(hostname, port);
  printf("testr2\n");

  ASSERT_TRUE(context == nullptr);
  ASSERT_TRUE(errno == ENOMEM);
  free(context);
}

TEST(redisinit, failed_connection) {
  const char *hostname = "localhost";
  uint32_t port = 4177;
  _GTEST_REDIS_CONTEX = (redisContext *)malloc(sizeof(redisContext));
  _GTEST_REDIS_CONTEX->err = REDIS_ERR_EOF; // some error

  printf("test\n");
  redisContext *context = db_init(hostname, port);
  printf("testr2\n");

  ASSERT_TRUE(context == nullptr);
  ASSERT_TRUE(errno == ECONNREFUSED);
  free(context);
}

TEST(redisinit, NULL_hostname) {
  const char *hostname = NULL;
  uint32_t port = 4177;

  redisContext *context = db_init(hostname, port);

  ASSERT_TRUE(context == nullptr);
  ASSERT_TRUE(errno == EINVAL);
  free(context);
}

TEST(redisinit, NULL_port) {
  const char *hostname = "localhost";
  uint32_t port = 0;

  redisContext *context = db_init(hostname, port);

  ASSERT_TRUE(context == nullptr);
  ASSERT_TRUE(errno == EINVAL);
  free(context);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
