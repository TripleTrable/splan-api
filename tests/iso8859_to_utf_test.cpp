#include <cerrno>
#include <fcntl.h>
#include <gtest/gtest.h>

extern "C"
{
#include "splan/json/spapi.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
}

// just need one test, as the parameters are always correct from libcurl
// Should any parameter be different than here, this is a severe bug in libcurl
TEST(iso8859_1_to_utf_8,correct_string)
{

    int iso_fd = open("./iso8859_test.txt", O_RDONLY);
    int utf_fd = open("./utf_8_test.txt", O_RDONLY);

    struct stat iso_stat;
    fstat(iso_fd, &iso_stat);

    struct stat utf_stat;
    fstat(utf_fd, &utf_stat);

    char *iso_map =
        (char *)mmap(0, iso_stat.st_size, PROT_READ, MAP_PRIVATE, iso_fd, 0);

    char *utf_map =
        (char *)mmap(0, utf_stat.st_size, PROT_READ, MAP_PRIVATE, utf_fd, 0);

    char *iso_str = (char *)calloc(iso_stat.st_size +1, sizeof(char));
    char *utf_str = (char *)calloc(utf_stat.st_size +1, sizeof(char));

    char *result = iso8859_1_to_utf_8(iso_str);

    ASSERT_STREQ(result,utf_str);


    munmap(iso_map, iso_stat.st_size);
    munmap(utf_map, utf_stat.st_size);

    close(iso_fd);
    close(utf_fd);
}

TEST(iso8859_1_to_utf_8,no_input)
{


    char * iso_str = NULL;
    char *result = iso8859_1_to_utf_8(iso_str);

    ASSERT_STREQ(result,NULL);
    ASSERT_EQ(errno,EINVAL);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
