/// Resizable array of any type. Macros used replace the current pointer by
/// another on resize, so keeping multiple pointers to the same vector is not
/// safe

#pragma once

#include <malloc.h>
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "../exception.h"
#include "../logging.h"

#define VECTOR_DEFAULT_CAPACITY 2
#define VECTOR_OFFSET 16UL  // >= sizeof(VectorData), 16 to align properly

/// @brief Struct to store the vector data, stored before the vector pointer
/// @param length length of the vector
/// @param capacity current capacity of the vector
/// @param stride size of the type of elements of the vector
typedef struct {
    uint32_t length;
    uint32_t capacity;
    uint32_t stride;
} VectorData;

// Private functions
void *_vector_create(int stride);
void *_vector_push(void *vector, void *value);
void *_vector_pop(int line, const char *file, void *vector, void *value);
void _vector_vector_pop_at(int line, const char *file, void *vector,
                           uint32_t index, void *value);
void _print_vector(void *vector, bool beautify, bool logger,
                   void (*print)(const void *), int line, const char *file);
void _print_vector2d(void *vector, bool beautify, void (*print)(const void *),
                     int line, const char *file);
bool _vector_contains(void *vector, void *value);
int32_t _vector_index_of(void *vector, void *value);
void *_vector_concat(void *vector, void *other);

/// @brief Free the vector
/// @param vector pointer to the vector
void vector_free(void *vector);

/// @brief Get the length of the vector
/// @param vector pointer to the vector
uint32_t vector_length(void *vector);

/// @brief Get the capacity of the vector
/// @param vector pointer to the vector
uint32_t vector_capacity(void *vector);

/// @brief Get the type size of the vector
/// @param vector pointer to the vector
uint32_t vector_stride(void *vector);

/// @brief Create an empty vector
/// @param type type of the elements of the vector
/// @return `void*` - pointer to the vector
#define vector_create(type) _vector_create(sizeof(type))

/// @brief Push a value to the vector
/// @param vector pointer to the vector
/// @param value value to push
#define vector_push(vector, value)           \
    {                                        \
        typeof(value) tmp = value;           \
        vector = _vector_push(vector, &tmp); \
    }

/// @brief Pop a value from the vector
/// @param vector pointer to the vector
/// @param value pointer to store the value
#define vector_pop(vector, value) \
    { vector = _vector_pop(__LINE__, __FILE__, vector, value); }

/// @brief Pop a value from the vector at a specific index
/// @param vector pointer to the vector
/// @param index index to pop
/// @param value pointer to store the value
#define vector_pop_at(vector, index, value) \
    _vector_vector_pop_at(__LINE__, __FILE__, vector, index, value)

/// @brief Check if the vector is empty
/// @param vector pointer to the vector
/// @return `bool` - true if the vector is empty, false otherwise
bool vector_is_empty(void *vector);

/// @brief Check if the vector contains a value
/// @param vector pointer to the vector
/// @param value value to check
#define vector_contains(vector, value)  \
    ({                                  \
        typeof(value) tmp = value;      \
        _vector_contains(vector, &tmp); \
    })

/// @brief Get the index of a value in the vector
/// @param vector pointer to the vector
/// @param value value to check
/// @return `int32_t` - index of the value, -1 if not found
#define vector_index_of(vector, value)  \
    ({                                  \
        typeof(value) tmp = value;      \
        _vector_index_of(vector, &tmp); \
    })

/// @brief Map the vector using a function
/// @param vector pointer to the vector
/// @param map function to map the elements
void vector_map(void *vector, void (*map)(void *));

/// @brief Concatenate an vector to another
/// @param vector pointer to the vector
/// @param other pointer to the other vector
#define vector_concat(vector, other) vector = _vector_concat(vector, other)

/// @brief Sort the vector using quick sort
/// @param vector pointer to the vector
/// @param compare function to compare the elements
void vector_quick_sort(void *vector,
                       int (*compare)(const void *, const void *));

/// @brief Print the vector
/// @param vector pointer to the vector
/// @param beautify if true, print the vector in a beautified way
/// @param print function to print the elements
#define print_vector(vector, beautify, print) \
    _print_vector(vector, beautify, true, print, __LINE__, __FILE__)

/// @brief Print the vector without logger
/// @param vector pointer to the vector
/// @param beautify if true, print the vector in a beautified way
/// @param print function to print the elements
#define print_vector_no_logger(vector, beautify, print) \
    _print_vector(vector, beautify, false, print, __LINE__, __FILE__)

/// @brief Print a 2D vector
/// @param vector pointer to the vector
/// @param beautify if true, print the vector in a beautified way
/// @param print function to print the elements
#define print_vector2d(vector, beautify, print) \
    _print_vector2d(vector, beautify, print, __LINE__, __FILE__)

void _print_int(const void *a);
void _print_float(const void *a);
void _print_double(const void *a);
void _print_char(const void *a);

/// @brief Print an vector of integers
/// @param vector pointer to the vector
/// @param beautify if true, print the vector in a beautified way
#define print_int_vector(vector, beautify) \
    print_vector(vector, beautify, _print_int)
/// @brief Print a 2D vector of integers
/// @param vector pointer to the vector
/// @param beautify if true, print the vector in a beautified way
#define print_int_vector2d(vector, beautify) \
    print_vector2d(vector, beautify, _print_int)

/// @brief Print an vector of floats
/// @param vector pointer to the vector
/// @param beautify if true, print the vector in a beautified way
#define print_float_vector(vector, beautify) \
    print_vector(vector, beautify, _print_float)
/// @brief Print a 2D vector of floats
/// @param vector pointer to the vector
/// @param beautify if true, print the vector in a beautified way
#define print_float_vector2d(vector, beautify) \
    print_vector2d(vector, beautify, _print_float)

/// @brief Print an vector of doubles
/// @param vector pointer to the vector
/// @param beautify if true, print the vector in a beautified way
#define print_double_vector(vector, beautify) \
    print_vector(vector, beautify, _print_double)
/// @brief Print a 2D vector of doubles
/// @param vector pointer to the vector
/// @param beautify if true, print the vector in a beautified way
#define print_double_vector2d(vector, beautify) \
    print_vector2d(vector, beautify, _print_double)

/// @brief Print an vector of characters
/// @param vector pointer to the vector
/// @param beautify if true, print the vector in a beautified way
#define print_char_vector(vector, beautify) \
    print_vector(vector, beautify, _print_char)
/// @brief Print a 2D vector of characters
/// @param vector pointer to the vector
/// @param beautify if true, print the vector in a beautified way
#define print_char_vector2d(vector, beautify) \
    print_vector2d(vector, beautify, _print_char)
