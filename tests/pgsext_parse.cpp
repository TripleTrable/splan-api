
#include <gtest/gtest.h>

extern "C" {
#include "splan/json/spapi.h"
#include "splan/spdata.h"
}

TEST(pgsext_parser, ok) {
  const char *json =
      R"_([[{"id":14119,"shortname":"INF-M/FWPM","name":"Masterstudiengang Informatik - fachwissenschaftliche Wahlpflichtmodule","lectures":[{"id":4721,"shortname":"DL","name":"Deep Learning","pgid":14119},{"id":4166,"shortname":"DSP","name":"Digital Signal Processing and Machine Learning","pgid":14119}]},{"id":13815,"shortname":"INF-M/Pflicht","name":"Masterstudiengang Informatik - Pflichtmodule","lectures":[{"id":3210,"shortname":"Fachschaft INF","name":"Fachschaft INF","pgid":13796},{"id":1072,"shortname":"MVI","name":"Mathematische Verfahren der Informatik","pgid":13815}]}]])_";
  std::array<pgsext, 2> expected;
  expected[0].id = 14119;
  expected[0].shortname = "INF-M/FWPM";
  expected[0].name =
      "Masterstudiengang Informatik - fachwissenschaftliche Wahlpflichtmodule";
  expected[0].lectures = NULL;
  expected[0].lecture_count = 2;

  expected[1].id = 13815;
  expected[1].shortname = "INF-M/Pflicht";
  expected[1].name = "Masterstudiengang Informatik - Pflichtmodule";
  expected[1].lectures = NULL;
  expected[1].lecture_count = 2;

  pgsext *result = pgsext_parse_json(json);

  ASSERT_TRUE(result != nullptr);
  EXPECT_EQ(expected[0].id, result[0].id);
  EXPECT_STREQ(expected[0].shortname, result[0].shortname);
  EXPECT_STREQ(expected[0].name, result[0].name);
  EXPECT_EQ(expected[0].lecture_count, result[0].lecture_count);

  EXPECT_EQ(expected[1].id, result[1].id);
  EXPECT_STREQ(expected[1].shortname, result[1].shortname);
  EXPECT_STREQ(expected[1].name, result[1].name);
  EXPECT_EQ(expected[1].lecture_count, result[1].lecture_count);
  free(result);
}

TEST(pgsext_parser, null_string) {

  const pgsext *result = pgsext_parse_json(NULL);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(pgsext_parser, wrong_short_name) {
  const char *json =
      R"_([[{"id":14119,"shortname":1,"name":"Masterstudiengang Informatik - fachwissenschaftliche Wahlpflichtmodule","lectures":[{"id":4721,"shortname":"DL","name":"Deep Learning","pgid":14119},{"id":4166,"shortname":"DSP","name":"Digital Signal Processing and Machine Learning","pgid":14119}]},{"id":13815,"shortname":"INF-M/Pflicht","name":"Masterstudiengang Informatik - Pflichtmodule","lectures":[{"id":3210,"shortname":"Fachschaft INF","name":"Fachschaft INF","pgid":13796}]}]])_";

  const pgsext *result = pgsext_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(pgsext_parser, wrong_name) {
  const char *json =
      R"_([[{"id":14119,"shortname":"INF-M/FWPM","name":1,"lectures":[{"id":4721,"shortname":"DL","name":"Deep Learning","pgid":14119},{"id":4166,"shortname":"DSP","name":"Digital Signal Processing and Machine Learning","pgid":14119}]},{"id":13815,"shortname":"INF-M/Pflicht","name":"Masterstudiengang Informatik - Pflichtmodule","lectures":[{"id":3210,"shortname":"Fachschaft INF","name":"Fachschaft INF","pgid":13796}]}]])_";

  const pgsext *result = pgsext_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(pgsext_parser, wrong_id) {
  const char *json =
      R"_([[{"id":"foo","shortname":"INF-M/FWPM","name":"Masterstudiengang Informatik - fachwissenschaftliche Wahlpflichtmodule","lectures":[{"id":4721,"shortname":"DL","name":"Deep Learning","pgid":14119},{"id":4166,"shortname":"DSP","name":"Digital Signal Processing and Machine Learning","pgid":14119}]}]])_";

  const pgsext *result = pgsext_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(pgsext_parser, wrong_lecture) {
  const char *json =
      R"_([[{"id":14119,"shortname":"INF-M/FWPM","name":"Masterstudiengang Informatik - fachwissenschaftliche Wahlpflichtmodule","lectures":"foo"}]])_";

  const pgsext *result = pgsext_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(pgsext_parser, junk_parameter) {
  const char *json =
      R"_([[{"id":14119,"shortname":"INF-M/FWPM","name":"Masterstudiengang Informatik - fachwissenschaftliche Wahlpflichtmodule","lectures":[{"id":4721,"shortname":"DL","name":"Deep Learning","pgid":14119},{"id":4166,"shortname":"DSP","name":"Digital Signal Processing and Machine Learning","pgid":14119}]},{"id":13815,"shortname":"INF-M/Pflicht","name":"Masterstudiengang Informatik - Pflichtmodule","lectures":[{"id":3210,"shortname":"Fachschaft INF","name":"Fachschaft INF","pgid":13796]}]])_";

  const pgsext *result = pgsext_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
