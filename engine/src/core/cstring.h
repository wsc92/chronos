#pragma once

#include "../defines.h"

// Returns the length of the given string
CAPI u64 string_length(const char* str);

CAPI char* string_duplicate(const char* str);

// case-sensitive string comparison. True if the same, otherwise False.
CAPI b8 strings_equal(const char* str0, const char* str1);


// Case-insensitive string comparison. True if the same, otherwise false.
CAPI b8 strings_equali(const char* str0, const char* str1);

/**
 * @brief Performs string formatting to dest given format string and parameters.
 * @param dest The destination for the formatted string.
 * @param format The format string to use for the operation
 * @param ... The format arguments.
 * @returns The length of the newly-formatted string.
 */
CAPI i32 string_format(char* dest, const char* format, ...);


/**
 * @brief Performs variadic string formatting to dest given format string and va_list.
 * @param dest The destination for the formatted string.
 * @param format The string to be formatted.
 * @param va_list The variadic argument list.
 * @returns The size of the data written.
 */
CAPI i32 string_format_v(char* dest, const char* format, void* va_list);
