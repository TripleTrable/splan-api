
#include <gtest/gtest.h>

extern "C" {
#include "splan/json/spapi.h"
#include "splan/spdata.h"
}

TEST(pus_parser, ok) {
  const char *json =
      R"_([[{"id":37,"shortname":"2024 SoSe","name":"Sommersemester 2024","startdate":"2024-03-15","enddate":"2024-09-30","dateasdefault":true,"defaultloc":null,"visibleonweb":true},{"id":34,"shortname":"2023 WS","name":"Wintersemester 2023/24","startdate":"2023-10-01","enddate":"2024-03-14","dateasdefault":true,"defaultloc":null,"visibleonweb":true}]])_";
  pu expected[2];
  expected[0].id = 37;
  expected[0].shortname = "2024 SoSe";
  expected[0].name = "Sommersemester 2024";
  expected[0].startdate = "2024-03-15";
  expected[0].enddate = "2024-09-30";
  expected[0].dateasdefault = 1;
  expected[0].defaultloc = NULL;
  expected[0].visibleonweb = 1;

  expected[1].id = 34;
  expected[1].shortname = "2023 WS";
  expected[1].name = "Wintersemester 2023/24";
  expected[1].startdate = "2023-10-01";
  expected[1].enddate = "2024-03-14";
  expected[1].dateasdefault = 1;
  expected[1].defaultloc = NULL;
  expected[1].visibleonweb = 1;

  pu *result = pus_parse_json(json);

  ASSERT_TRUE(result != nullptr);
  EXPECT_EQ(expected[0].id, result[0].id);
  EXPECT_STREQ(expected[0].shortname, result[0].shortname);
  EXPECT_STREQ(expected[0].name, result[0].name);
  EXPECT_STREQ(expected[0].startdate, result[0].startdate);
  EXPECT_STREQ(expected[0].enddate, result[0].enddate);
  EXPECT_EQ(expected[0].dateasdefault, result[0].dateasdefault);
  EXPECT_EQ(expected[0].defaultloc, result[0].defaultloc);
  EXPECT_EQ(expected[0].visibleonweb, result[0].visibleonweb);

  EXPECT_EQ(expected[1].id, result[1].id);
  EXPECT_STREQ(expected[1].shortname, result[1].shortname);
  EXPECT_STREQ(expected[1].name, result[1].name);
  EXPECT_STREQ(expected[1].startdate, result[1].startdate);
  EXPECT_STREQ(expected[1].enddate, result[1].enddate);
  EXPECT_EQ(expected[1].dateasdefault, result[1].dateasdefault);
  EXPECT_EQ(expected[1].defaultloc, result[1].defaultloc);
  EXPECT_EQ(expected[1].visibleonweb, result[1].visibleonweb);
  free(result);
}

TEST(pus_parser, null_string) {

  const pu *result = pus_parse_json(NULL);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(pus_parser, wrong_short_name) {
  const char *json =
      R"_([[{"id":37,"shortname":3,"name":"Sommersemester 2024","startdate":"2024-03-15","enddate":"2024-09-30","dateasdefault":true,"defaultloc":null,"visibleonweb":true},{"id":34,"shortname":"2023 WS","name":"Wintersemester 2023/24","startdate":"2023-10-01","enddate":"2024-03-14","dateasdefault":true,"defaultloc":null,"visibleonweb":true}]])_";

  const pu *result = pus_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(pus_parser, wrong_name) {
  const char *json =
      R"_([[{"id":37,"shortname":"2024 SoSe","name":3,"startdate":"2024-03-15","enddate":"2024-09-30","dateasdefault":true,"defaultloc":null,"visibleonweb":true},{"id":34,"shortname":"2023 WS","name":"Wintersemester 2023/24","startdate":"2023-10-01","enddate":"2024-03-14","dateasdefault":true,"defaultloc":null,"visibleonweb":true}]])_";

  const pu *result = pus_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(pus_parser, wrong_id) {
  const char *json =
      R"_([[{"id":"string","shortname":"2024 SoSe","name":"Sommersemester 2024","startdate":"2024-03-15","enddate":"2024-09-30","dateasdefault":true,"defaultloc":null,"visibleonweb":true},{"id":34,"shortname":"2023 WS","name":"Wintersemester 2023/24","startdate":"2023-10-01","enddate":"2024-03-14","dateasdefault":true,"defaultloc":null,"visibleonweb":true}]])_";

  const pu *result = pus_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(pus_parser, wrong_startdate) {
  const char *json =
      R"_([[{"id":37,"shortname":"2024 SoSe","name":"Sommersemester 2024","startdate":3,"enddate":"2024-09-30","dateasdefault":true,"defaultloc":null,"visibleonweb":true},{"id":34,"shortname":"2023 WS","name":"Wintersemester 2023/24","startdate":"2023-10-01","enddate":"2024-03-14","dateasdefault":true,"defaultloc":null,"visibleonweb":true}]])_";

  const pu *result = pus_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(pus_parser, wrong_enddate) {
  const char *json =
      R"_([[{"id":37,"shortname":"2024 SoSe","name":"Sommersemester 2024","startdate":"2024-03-15","enddate":3,"dateasdefault":true,"defaultloc":null,"visibleonweb":true},{"id":34,"shortname":"2023 WS","name":"Wintersemester 2023/24","startdate":"2023-10-01","enddate":"2024-03-14","dateasdefault":true,"defaultloc":null,"visibleonweb":true}]])_";

  const pu *result = pus_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(pus_parser, wrong_dateasdefault) {
  const char *json =
      R"_([[{"id":37,"shortname":"2024 SoSe","name":"Sommersemester 2024","startdate":"2024-03-15","enddate":"2024-09-30","dateasdefault":"blah","defaultloc":null,"visibleonweb":true},{"id":34,"shortname":"2023 WS","name":"Wintersemester 2023/24","startdate":"2023-10-01","enddate":"2024-03-14","dateasdefault":true,"defaultloc":null,"visibleonweb":true}]])_";

  const pu *result = pus_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(pus_parser, wrong_visibleweb) {
  const char *json =
      R"_([[{"id":37,"shortname":"2024 SoSe","name":"Sommersemester 2024","startdate":"2024-03-15","enddate":"2024-09-30","dateasdefault":true,"defaultloc":null,"visibleonweb":true},{"id":34,"shortname":"2023 WS","name":"Wintersemester 2023/24","startdate":"2023-10-01","enddate":"2024-03-14","dateasdefault":true,"defaultloc":null,"visibleonweb":"foo"}]])_";

  const pu *result = pus_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

TEST(pus_parser, junk_parameter) {
  const char *json =
      R"_([[{"id":37,"shortname":"2024 SoSe","name":"Sommersemester 2024","startdate":"2024-03-15","enddate":"2024-09-30","dateasdefault":true,"defaultloc":null,"visibleonweb":true},{"id":34,"shortname":"2023 WS","name":"Wintersemester 2023/24","startdate":"2023-10-01","enddate":"2024-03-14","dateasdefault":true,"defaultloc":null,"visibleonweb":true]])_";

  const pu *result = pus_parse_json(json);

  EXPECT_TRUE(result == nullptr);
  EXPECT_EQ(errno, EINVAL);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
