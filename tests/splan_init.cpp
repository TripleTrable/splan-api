#include <gtest/gtest.h>

extern "C" {
#include "splan/spdata.h"
#include <errno.h>
}

TEST(splan_init, ok) {
  server_user_config data;
  data.server_api_endpoint = "server_URL";
  int ret = splan_init(&data); // GCOVR_EXCL_BR_LINE
  EXPECT_EQ(ret, 0);
  EXPECT_STREQ(_server_config.server_api_endpoint, data.server_api_endpoint);
}

TEST(splan_init, null_parameter) {

  int ret = splan_init(NULL); // GCOVR_EXCL_BR_LINE
  EXPECT_EQ(ret, -1);
  EXPECT_EQ(errno, EINVAL);
}

TEST(splan_init, null_api_endpoint) {

  server_user_config data;
  data.server_api_endpoint = NULL;
  int ret = splan_init(&data); // GCOVR_EXCL_BR_LINE
  EXPECT_EQ(ret, -1);
  EXPECT_EQ(errno, EINVAL);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
