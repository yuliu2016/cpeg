#ifndef CPEG_UNICODE_H
#define CPEG_UNICODE_H

#include "object.h"

VALUE FUnicode_from_ascii_and_size(const char * array, size_t len);

VALUE FUnicode_from_ascii(const char * array);

#endif //CPEG_UNICODE_H
