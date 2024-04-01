#include <cstdio>
#include <curl/curl.h>
#include <fcntl.h>
#include <gtest/gtest.h>
#include <sys/mman.h>

extern "C" {
#include "splan/curl/curl_dl.h"
#include "splan/spdata.h"
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

// just need one test, as the parameters are always correct from libcurl
// Should any parameter be different than here, this is a severe bug in libcurl
TEST(write_callback, Correct) {
  response_memory buffer_mem;
  buffer_mem.memory = (uint8_t *)malloc(1);
  buffer_mem.size = 0;

  const char *buffer = "==NEW TEST DATA==";
  const char *toAdd = "Test Data from previous run";
  const char *expect = "Test Data from previous run==NEW TEST DATA==";

  write_callback((void *)toAdd, 1, 27, (void *)&buffer_mem);
  write_callback((void *)buffer, 1, 17, (void *)&buffer_mem);

  EXPECT_STREQ((char *)buffer_mem.memory, expect);
}

TEST(curl_get, Correct) {
  int iso_fd = open("./curl_getlocs_raw.txt", O_RDONLY);
  ASSERT_NE(iso_fd, -1);
  struct stat iso_stat;
  fstat(iso_fd, &iso_stat);
  char *iso_map =
      (char *)mmap(0, iso_stat.st_size, PROT_READ, MAP_PRIVATE, iso_fd, 0);

  response_memory mem;

  mem.memory = (uint8_t *)calloc(iso_stat.st_size + 1, sizeof(char));
  mem.size = (iso_stat.st_size + 1) * sizeof(char);

  server_user_config data;
  data.server_api_endpoint = "https://splan.th-rosenheim.de/splan/json";
  splan_init(&data);

  memcpy(mem.memory, iso_map, iso_stat.st_size);

  _GTEST_CURL_RESPONSE_MOC_RET = CURLE_OK;
  _GTEST_CURL_RESPONSE_MEM = mem.memory;
  _GTEST_CURL_RESPONSE_MEM_SIZE = mem.size;

  const char *result =
      curl_get("https://splan.th-rosenheim.de/splan/json?m=getpus");

  ASSERT_TRUE(result != nullptr);
  EXPECT_STREQ((char *)mem.memory, result);

  munmap(iso_map, iso_stat.st_size);

  close(iso_fd);
}

TEST(curl_get, invalid_cert) {
  int iso_fd = open("./curl_getlocs_raw.txt", O_RDONLY);
  ASSERT_NE(iso_fd, -1);
  struct stat iso_stat;
  fstat(iso_fd, &iso_stat);
  char *iso_map =
      (char *)mmap(0, iso_stat.st_size, PROT_READ, MAP_PRIVATE, iso_fd, 0);

  response_memory mem;

  mem.memory = (uint8_t *)calloc(iso_stat.st_size + 1, sizeof(char));
  mem.size = (iso_stat.st_size + 1) * sizeof(char);

  server_user_config data;
  data.server_api_endpoint = "https://splan.th-rosenheim.de/splan/json";
  splan_init(&data);

  memcpy(mem.memory, iso_map, iso_stat.st_size);

  _GTEST_CURL_RESPONSE_MOC_RET = CURLE_SSL_INVALIDCERTSTATUS;
  _GTEST_CURL_RESPONSE_MEM = mem.memory;
  _GTEST_CURL_RESPONSE_MEM_SIZE = mem.size;

  const char *result =
      curl_get("https://splan.th-rosenheim.de/splan/json?m=getpuss");

  EXPECT_TRUE(result == nullptr);

  munmap(iso_map, iso_stat.st_size);

  close(iso_fd);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
