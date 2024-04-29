
#include <cjson/cJSON.h>
#include <gtest/gtest.h>

extern "C" {
#include "splan/json/spapi.h"
#include "splan/spdata.h"
}

TEST(lectures_parser, ok) {
  const char *json =
      R"_([{"id":4721,"shortname":"DL","name":"Deep Learning","pgid":14119},{"id":4166,"shortname":"DSP","name":"Digital Signal Processing and Machine Learning","pgid":14119}])_";
  std::array<lecture, 2> expected;
  expected[0].id = 4721;
  expected[0].shortname = "DL";
  expected[0].name = "Deep Learning";
  expected[0].pgid = 14119;

  expected[1].id = 4166;
  expected[1].shortname = "DSP";
  expected[1].name = "Digital Signal Processing and Machine Learning";
  expected[1].pgid = 14119;

  const cJSON *data = cJSON_Parse(json);
  ASSERT_TRUE(data != nullptr);
  size_t size;
  lecture *result = lecture_parse(data, &size);

  ASSERT_TRUE(result != nullptr);
  EXPECT_EQ(expected[0].id, result[0].id);
  EXPECT_STREQ(expected[0].shortname, result[0].shortname);
  EXPECT_STREQ(expected[0].name, result[0].name);
  EXPECT_EQ(expected[0].pgid, result[0].pgid);

  EXPECT_EQ(expected[1].id, result[1].id);
  EXPECT_STREQ(expected[1].shortname, result[1].shortname);
  EXPECT_STREQ(expected[1].name, result[1].name);
  EXPECT_EQ(expected[1].pgid, result[1].pgid);
  free(result);
}

TEST(lectures_parser, null_string) {

  size_t size;
  const lecture *result = lecture_parse(NULL, &size);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(lectures_parser, wrong_short_name) {
  const char *json =
      R"_([{"id":4721,"shortname":1,"name":"Deep Learning","pgid":14119}])_";

  size_t size;
  const cJSON *data = cJSON_Parse(json);
  ASSERT_TRUE(data != nullptr);
  const lecture *result = lecture_parse(data, &size);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(lectures_parser, wrong_name) {
  const char *json =
      R"_([{"id":4721,"shortname":"DL","name":1,"pgid":14119}])_";

  size_t size;
  const cJSON *data = cJSON_Parse(json);
  ASSERT_TRUE(data != nullptr);
  const lecture *result = lecture_parse(data, &size);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(lectures_parser, wrong_id) {
  const char *json =
      R"_([{"id":"foo","shortname":"DL","name":"Deep Learning","pgid":14119}])_";

  size_t size;
  const cJSON *data = cJSON_Parse(json);
  ASSERT_TRUE(data != nullptr);
  const lecture *result = lecture_parse(data, &size);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(lectures_parser, wrong_pgid) {
  const char *json =
      R"_([{"id":4721,"shortname":"DL","name":"Deep Learning","pgid":"foo"}])_";

  size_t size;
  const cJSON *data = cJSON_Parse(json);
  ASSERT_TRUE(data != nullptr);
  const lecture *result = lecture_parse(data, &size);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
