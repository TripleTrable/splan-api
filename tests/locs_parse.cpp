
#include <gtest/gtest.h>

extern "C" {
#include "splan/json/spapi.h"
#include "splan/spdata.h"
}

TEST(locs_parser, ok) {
  const char *json =
      R"_([[{"id":3,"shortname":"*RO","name":"Rosenheim (Hochschule)"},{"id":5,"shortname":"WS","name": "Wasserburg (RoMed Klinik)"}]])_";
  std::array<loc, 2> expected;
  expected[0].id = 3;
  expected[0].shortname = "*RO";
  expected[0].name = "Rosenheim (Hochschule)";

  expected[1].id = 5;
  expected[1].shortname = "WS";
  expected[1].name = "Wasserburg (RoMed Klinik)";

  loc *result = locs_parse_json(json);

  ASSERT_TRUE(result != nullptr);
  EXPECT_EQ(result[0].id, expected[0].id);
  EXPECT_STREQ(result[0].shortname, expected[0].shortname);
  EXPECT_STREQ(result[0].name, expected[0].name);

  EXPECT_EQ(result[1].id, expected[1].id);
  EXPECT_STREQ(result[1].shortname, expected[1].shortname);
  EXPECT_STREQ(result[1].name, expected[1].name);
  free(result);
}

TEST(locs_parser, null_string) {

  const loc *result = locs_parse_json(NULL);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(locs_parser, wrong_short_name) {
  const char *json =
      R"_([[{"id":3,"shortname":3,"name":"Rosenheim (Hochschule)"},{"id":5,"shortname":"WS","name": "Wasserburg (RoMed Klinik)"}]])_";

  const loc *result = locs_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(locs_parser, wrong_name) {
  const char *json =
      R"_([[{"id":3,"shortname":"*RO","name":3},{"id":5,"shortname":"WS","name": "Wasserburg (RoMed Klinik)"}]])_";

  const loc *result = locs_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(locs_parser, wrong_id) {
  const char *json =
      R"_([[{"id":"string","shortname":"*RO","name":"Rosenheim (Hochschule)"},{"id":5,"shortname":"WS","name": "Wasserburg (RoMed Klinik)"}]])_";

  const loc *result = locs_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(locs_parser, junk_parameter) {
  const char *json =
      R"_([[{"id":"string","shortname":"*RO","name":"Rosenheim (Hochschule)"}{"id":5,"shortname":"WS","name": "Wasserburg (RoMed Klinik)"]])_";

  const loc *result = locs_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
