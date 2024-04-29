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

TEST(getogs, ok) {
  int iso_fd = open("./curl_getogs_raw.txt", O_RDONLY);
  ASSERT_NE(iso_fd, -1);
  struct stat iso_stat;
  fstat(iso_fd, &iso_stat);
  pu faculty = {.id = 37};
  char *iso_map =
      (char *)mmap(0, iso_stat.st_size, PROT_READ, MAP_PRIVATE, iso_fd, 0);

  response_memory mem;

  mem.memory = (uint8_t *)calloc(iso_stat.st_size + 1, sizeof(char));
  mem.size = (iso_stat.st_size + 1) * sizeof(char);

  std::array<og, 2> expected;
  expected[0].id = 105;
  expected[0].shortname = "AAI-B";
  expected[0].name = "Bachelorstudiengang Applied Artificial Intelligence";

  expected[1].id = 41;
  expected[1].shortname = "AFE-M";
  expected[1].name = "Masterstudiengang Angewandte Forschung & Entwicklung in "
                     "den Ingenieurwissenschaften";

  server_user_config data;
  data.server_api_endpoint = "https://splan.th-rosenheim.de/splan/json";
  splan_init(&data);

  memcpy(mem.memory, iso_map, iso_stat.st_size);

  _GTEST_CURL_RESPONSE_MOC_RET = CURLE_OK;
  _GTEST_CURL_RESPONSE_MEM = mem.memory;
  _GTEST_CURL_RESPONSE_MEM_SIZE = mem.size;

  const og *result = splan_get_ogs(&faculty);

  ASSERT_TRUE(result != nullptr);
  EXPECT_EQ(expected[0].id, result[0].id);
  EXPECT_STREQ(expected[0].shortname, result[0].shortname);
  EXPECT_STREQ(expected[0].name, result[0].name);

  EXPECT_EQ(expected[1].id, result[1].id);
  EXPECT_STREQ(expected[1].shortname, result[1].shortname);
  EXPECT_STREQ(expected[1].name, result[1].name);

  munmap(iso_map, iso_stat.st_size);

  close(iso_fd);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
