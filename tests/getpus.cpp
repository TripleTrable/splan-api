#include <curl/curl.h>
#include <fcntl.h>
#include <gtest/gtest.h>
#include <sys/mman.h>

extern "C" {
#include "splan/json/spapi.h"
#include <string.h>
size_t write_callback(void *, size_t, size_t, void *);

int _GTEST_CURL_RESPONSE_MOC_RET;
uint8_t *_GTEST_CURL_RESPONSE_MEM;
size_t _GTEST_CURL_RESPONSE_MEM_SIZE;

typedef struct {
  uint8_t *memory;
  size_t size;
} response_memory;
}

TEST(getpus, ok) {
  int iso_fd = open("./curl_getpus_raw.txt", O_RDONLY);
  ASSERT_NE(iso_fd, -1);
  struct stat iso_stat;
  fstat(iso_fd, &iso_stat);
  char *iso_map =
      (char *)mmap(0, iso_stat.st_size, PROT_READ, MAP_PRIVATE, iso_fd, 0);

  response_memory mem;

  mem.memory = (uint8_t *)calloc(iso_stat.st_size + 1, sizeof(char));
  mem.size = (iso_stat.st_size + 1) * sizeof(char);

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

  server_user_config data;
  data.server_api_endpoint = "https://splan.th-rosenheim.de/splan/json";
  splan_init(&data);

  memcpy(mem.memory, iso_map, iso_stat.st_size);

  _GTEST_CURL_RESPONSE_MOC_RET = CURLE_OK;
  _GTEST_CURL_RESPONSE_MEM = mem.memory;
  _GTEST_CURL_RESPONSE_MEM_SIZE = mem.size;

  const pu *result = splan_get_pus();

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

  munmap(iso_map, iso_stat.st_size);

  close(iso_fd);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
