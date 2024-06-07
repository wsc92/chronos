#pragma once

#include "../defines.h"

// Returns the length of the given string
CAPI u64 string_length(const char* str);

CAPI char* string_duplicate(const char* str);

// case-sensitive string comparison. True if the same, otherwise False.
CAPI b8 strings_equal(const char* str0, const char* str1);
