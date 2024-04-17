#include <curl/curl.h>
#include <fcntl.h>
#include <gtest/gtest.h>
#include <pthread.h>
#include <sys/mman.h>

extern "C" {
#include "rest/default_route.h"
#include <microhttpd.h>
#include <string.h>

char *simple_message(const char *message);
struct MHD_Response *create_MHD_response(char *message);
}

TEST(simple_message, ok) {
  const char *message = "Hello, World!";
  const char *expect = R"_({"message": "Hello, World!"})_";

  const char *ret = simple_message(message);

  EXPECT_STREQ(expect, ret);
}

TEST(simple_message, null) {
  const char *message = NULL;
  const char *expect = NULL;

  char *ret = simple_message(message);

  EXPECT_EQ(expect, ret);
  EXPECT_EQ(errno, EINVAL);
}

TEST(create_MHD_response, ok) {
  const char *message = "Hello, World";

  struct MHD_Response *ret = create_MHD_response((char *)message);

  EXPECT_NE(NULL, *(long *)&ret);
}

TEST(create_MHD_response, null_message) {
  const char *message = NULL;

  struct MHD_Response *ret = create_MHD_response((char *)message);

  EXPECT_EQ(NULL, *(long *)&ret);
  EXPECT_EQ(errno, EINVAL);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
