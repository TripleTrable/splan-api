#include <gtest/gtest.h>

extern "C" {
#include "splan/spdata.h"
}

TEST(splan_init, ok) {
  server_user_config data;
  data.server_api_endpoint = "server_URL";
  splan_init(&data);
  EXPECT_STREQ(_server_config.server_api_endpoint, data.server_api_endpoint);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
