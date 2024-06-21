#include <gtest/gtest.h>

extern "C" {
#include "splan/spdata.h"
#include <errno.h>
#include <hiredis/hiredis.h>
}

// As double free returns an runtime error or segfault this is a valid test
// witout any asserts. For missing frees. these tests are run manually with
// valgrind

TEST(locfree, ok) {
  loc *data = (loc *)malloc(sizeof(loc));
  data->name = (char *)malloc(32);
  data->shortname = (char *)malloc(4);

  loc_free(data);

  ASSERT_TRUE(1);
}

TEST(pufree, ok) {
  pu *data = (pu *)malloc(sizeof(pu));
  data->name = (char *)malloc(32);
  data->shortname = (char *)malloc(4);
  data->startdate = (char *)malloc(4);
  data->enddate = (char *)malloc(4);

  loc *def = (loc *)malloc(sizeof(loc));
  def->name = (char *)malloc(32);
  def->shortname = (char *)malloc(4);

  pu_free(data);

  ASSERT_TRUE(1);
}

TEST(ogfree, ok) {
  og *data = (og *)malloc(sizeof(og));
  data->name = (char *)malloc(32);
  data->shortname = (char *)malloc(4);

  og_free(data);

  ASSERT_TRUE(1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
