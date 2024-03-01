#ifndef STR_H
#define STR_H
#include <malloc.h>
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "exception.h"

#define STRING_DEFAULT_CAPACITY 2
#define STRING_ELEMENT_SIZE sizeof(char)


/// @brief Struct to store the string and its data
typedef struct {
    char *data;
    uint32_t length;
    uint32_t capacity;
} String;

// Private funcs
void _string_push(String *string, String *other);
void _string_push_cstr(String *string, char *other);
char _string_get(int line, const char *file, String *string, uint32_t index);
void _string_set(int line, const char *file, String *string, uint32_t index, char value);
bool _string_compare(String *string, String *other);
bool _string_compare_cstr(String *string, char *other);


/// @brief Create an empty string
/// @return `String` - the string
String *string_create();

/// @brief Create a string from a C string
/// @param cstr the C string
/// @return `String` - the string
String *string_from(char *cstr);

/// @brief Free the string
void string_free(String *string);

/// @brief Get the character at the index of the string
/// @param string the string
/// @param index the index
/// @return `char` - the character at the index of the string
#define string_get(string, index) _string_get(__LINE__, __FILE__, string, index)

/// @brief Set the character at the index of the string
/// @param string the string
/// @param index the index
/// @param value the value
#define string_set(string, index, value) _string_set(__LINE__, __FILE__, string, index, value)

/// @brief Append a character to the string
/// @param string the string
/// @param value the value
void string_append(String *string, char value);

/// @brief Push a string to the string
/// @param string the string
/// @param other the other string
#define string_push(string, other) _Generic((other), \
    String*: _string_push, \
    char*: _string_push_cstr, \
    default: _string_push_cstr)(string, other)

/// @brief Concatenate two strings
/// @param string the string
/// @param other the other string
/// @return `String` - the concatenated string
String *string_concat(String *string, String *other);

/// @brief Compare two strings
/// @param string the string
/// @param other the other string
/// @return `bool` - true if the strings are equal, false otherwise
#define string_compare(string, other) _Generic((other), \
    String*: _string_compare, \
    char*: _string_compare_cstr, \
    default: _string_compare_cstr)(string, other)

/// @brief Check if the string contains a character
/// @param string the string
/// @param value the value
/// @return `bool` - true if the string contains the character, false otherwise
bool string_contains(String *string, char value);



#endif  // STR_H