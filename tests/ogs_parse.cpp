
#include <gtest/gtest.h>

extern "C" {
#include "splan/json/spapi.h"
#include "splan/spdata.h"
}

TEST(ogs_parser, ok) {
  const char *json =
      R"_([[{"id":105,"shortname":"AAI-B","name":"Bachelorstudiengang Applied Artificial Intelligence"},{"id":41,"shortname":"AFE-M","name":"Masterstudiengang Angewandte Forschung & Entwicklung in den Ingenieurwissenschaften"}]])_";
  std::array<og, 2> expected;
  expected[0].id = 105;
  expected[0].shortname = "AAI-B";
  expected[0].name = "Bachelorstudiengang Applied Artificial Intelligence";

  expected[1].id = 41;
  expected[1].shortname = "AFE-M";
  expected[1].name = "Masterstudiengang Angewandte Forschung & Entwicklung in "
                     "den Ingenieurwissenschaften";

  og *result = ogs_parse_json(json);

  ASSERT_TRUE(result != nullptr);
  EXPECT_EQ(result[0].id, expected[0].id);
  EXPECT_STREQ(result[0].shortname, expected[0].shortname);
  EXPECT_STREQ(result[0].name, expected[0].name);

  EXPECT_EQ(result[1].id, expected[1].id);
  EXPECT_STREQ(result[1].shortname, expected[1].shortname);
  EXPECT_STREQ(result[1].name, expected[1].name);
  free(result);
}

TEST(ogs_parser, null_string) {

  const og *result = ogs_parse_json(NULL);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(ogs_parser, wrong_short_name) {
  const char *json =
      R"_([[{"id":105,"shortname":1,"name":"Bachelorstudiengang Applied Artificial Intelligence"},{"id":41,"shortname":"AFE-M","name":"Masterstudiengang Angewandte Forschung & Entwicklung in den Ingenieurwissenschaften"}]])_";

  const og *result = ogs_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(ogs_parser, wrong_name) {
  const char *json =
      R"_([[{"id":105,"shortname":"AAI-B","name":1},{"id":41,"shortname":"AFE-M","name":"Masterstudiengang Angewandte Forschung & Entwicklung in den Ingenieurwissenschaften"}]])_";

  const og *result = ogs_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(ogs_parser, wrong_id) {
  const char *json =
      R"_([[{"id":"foo","shortname":"AAI-B","name":"Bachelorstudiengang Applied Artificial Intelligence"},{"id":41,"shortname":"AFE-M","name":"Masterstudiengang Angewandte Forschung & Entwicklung in den Ingenieurwissenschaften"}]])_";

  const og *result = ogs_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(ogs_parser, junk_parameter) {
  const char *json =
      R"_([[{"id":105,"shortname":"AAI-B","name":"Bachelorstudiengang Applied Artificial Intelligence"{"id":41,"shortname":"AFE-M","name":"Masterstudiengang Angewandte Forschung & Entwicklung in den Ingenieurwissenschaften"}]])_";

  const og *result = ogs_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
