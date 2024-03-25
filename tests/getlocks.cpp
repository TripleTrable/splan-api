#include <gtest/gtest.h>

extern "C" {
#include "splan/json/spapi.h"
#include <string.h>
size_t write_callback(void *, size_t, size_t, void *);

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

  char *buffer = "==NEW TEST DATA==";
  char *toAdd = "Test Data from previous run";
  char *expect = "Test Data from previous run==NEW TEST DATA==";

  write_callback((void *)toAdd, 1, 27, (void *)&buffer_mem);
  write_callback((void *)buffer, 1, 17, (void *)&buffer_mem);

  EXPECT_STREQ((char *)buffer_mem.memory, expect);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
