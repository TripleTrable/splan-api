#include <asm-generic/errno-base.h>
#include <iconv.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *iso8859_1_to_utf_8(char *iso)
{
    iconv_t iconvDesc;

    size_t iconv_value;
    char *utf8_buffer;
    size_t len;
    size_t utf8_len;
    char *utf8_iter;

    if (!iso) {
        errno = EINVAL;
        return NULL;
    }

    iconvDesc = iconv_open("UTF-8//TRANSLIT//IGNORE", "ISO−8859-1");

    if (iconvDesc == (iconv_t)-1) {
        errno = EAGAIN;
        return NULL;
    }

    len = strlen(iso);
    if (!len) {
        errno = EINVAL;
        return NULL;
    }

    utf8_len = 2 * len;
    utf8_buffer = calloc(utf8_len, sizeof(char));

    if (!utf8_buffer) {
        errno = ENOMEM;
        return NULL;
    }

    utf8_iter = utf8_buffer;

    iconv_value = iconv(iconvDesc, &iso, &len, &utf8_iter, &utf8_len);

    if (iconv_value == (size_t)-1) {
        return NULL;
    }

    return utf8_buffer;
}
