#ifndef ARRAY_H
#define ARRAY_H
#include <malloc.h>
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "exception.h"
#include "logging.h"

#define ARRAY_DEFAULT_CAPACITY 2
#define ARRAY_OFFSET 16UL  // >= sizeof(ArrayData), 16 to align properly

/// @brief Struct to store the array data, stored before the array pointer
/// @param length length of the array
/// @param capacity current capacity of the array
/// @param type_size size of the type of elements of the array
typedef struct {
    uint32_t length;
    uint32_t capacity;
    uint32_t type_size;
} ArrayData;

// Private functions
void *_array_create(int type_size);
void *_array_push(void *array, void *value);
void *_array_pop(int line, const char *file, void *array, void *value);
void _array_array_pop_at(int line, const char *file, void *array,
                         uint32_t index, void *value);
void _print_array(const void *array, bool beautify, bool logger,
                  void (*print)(const void *), int line, const char *file);
void _print_array2d(const void *array, bool beautify,
                    void (*print)(const void *), int line, const char *file);
bool _array_contains(void *array, void *value);
int32_t _array_index_of(void *array, void *value);
void *_array_concat(void *array, void *other);

/// @brief Free the array
/// @param array pointer to the array
void array_free(void *array);

/// @brief Get the length of the array
/// @param array pointer to the array
uint32_t array_length(void *array);

/// @brief Get the capacity of the array
/// @param array pointer to the array
uint32_t array_capacity(void *array);

/// @brief Get the type size of the array
/// @param array pointer to the array
uint32_t array_type_size(void *array);

/// @brief Create an empty array
/// @param type type of the elements of the array
/// @return `void*` - pointer to the array
#define array_create(type) _array_create(sizeof(type))

/// @brief Push a value to the array
/// @param array pointer to the array
/// @param value value to push
#define array_push(array, value)          \
    {                                     \
        typeof(value) tmp = value;        \
        array = _array_push(array, &tmp); \
    }

/// @brief Pop a value from the array
/// @param array pointer to the array
/// @param value pointer to store the value
#define array_pop(array, value) \
    { array = _array_pop(__LINE__, __FILE__, array, value); }

/// @brief Pop a value from the array at a specific index
/// @param array pointer to the array
/// @param index index to pop
/// @param value pointer to store the value
#define array_pop_at(array, index, value) \
    _array_array_pop_at(__LINE__, __FILE__, array, index, value)

/// @brief Check if the array is empty
/// @param array pointer to the array
/// @return `bool` - true if the array is empty, false otherwise
bool array_is_empty(void *array);

/// @brief Check if the array contains a value
/// @param array pointer to the array
/// @param value value to check
#define array_contains(array, value)  \
    ({                                \
        typeof(value) tmp = value;    \
        _array_contains(array, &tmp); \
    })

/// @brief Get the index of a value in the array
/// @param array pointer to the array
/// @param value value to check
/// @return `int32_t` - index of the value, -1 if not found
#define array_index_of(array, value)  \
    ({                                \
        typeof(value) tmp = value;    \
        _array_index_of(array, &tmp); \
    })

/// @brief Map the array using a function
/// @param array pointer to the array
/// @param map function to map the elements
void array_map(void *array, void (*map)(void *));

/// @brief Concatenate an array to another
/// @param array pointer to the array
/// @param other pointer to the other array
#define array_concat(array, other) array = _array_concat(array, other)

/// @brief Sort the array using quick sort
/// @param array pointer to the array
/// @param compare function to compare the elements
void array_quick_sort(void *array, int (*compare)(const void *, const void *));


/// @brief Print the array
/// @param array pointer to the array
/// @param beautify if true, print the array in a beautified way
/// @param print function to print the elements
#define print_array(array, beautify, print) \
    _print_array(array, beautify, true, print, __LINE__, __FILE__)

/// @brief Print the array without logger
/// @param array pointer to the array
/// @param beautify if true, print the array in a beautified way
/// @param print function to print the elements
#define print_array_no_logger(array, beautify, print) \
    _print_array(array, beautify, false, print, __LINE__, __FILE__)

/// @brief Print a 2D array
/// @param array pointer to the array
/// @param beautify if true, print the array in a beautified way
/// @param print function to print the elements
#define print_array2d(array, beautify, print) \
    _print_array2d(array, beautify, print, __LINE__, __FILE__)

void _print_int(const void *a);
void _print_float(const void *a);
void _print_double(const void *a);
void _print_char(const void *a);

/// @brief Print an array of integers
/// @param array pointer to the array
/// @param beautify if true, print the array in a beautified way
#define print_int_array(array, beautify) \
    print_array(array, beautify, _print_int)
/// @brief Print a 2D array of integers
/// @param array pointer to the array
/// @param beautify if true, print the array in a beautified way
#define print_int_array2d(array, beautify) \
    print_array2d(array, beautify, _print_int)

/// @brief Print an array of floats
/// @param array pointer to the array
/// @param beautify if true, print the array in a beautified way
#define print_float_array(array, beautify) \
    print_array(array, beautify, _print_float)
/// @brief Print a 2D array of floats
/// @param array pointer to the array
/// @param beautify if true, print the array in a beautified way
#define print_float_array2d(array, beautify) \
    print_array2d(array, beautify, _print_float)

/// @brief Print an array of doubles
/// @param array pointer to the array
/// @param beautify if true, print the array in a beautified way
#define print_double_array(array, beautify) \
    print_array(array, beautify, _print_double)
/// @brief Print a 2D array of doubles
/// @param array pointer to the array
/// @param beautify if true, print the array in a beautified way
#define print_double_array2d(array, beautify) \
    print_array2d(array, beautify, _print_double)

/// @brief Print an array of characters
/// @param array pointer to the array
/// @param beautify if true, print the array in a beautified way
#define print_char_array(array, beautify) \
    print_array(array, beautify, _print_char)
/// @brief Print a 2D array of characters
/// @param array pointer to the array
/// @param beautify if true, print the array in a beautified way
#define print_char_array2d(array, beautify) \
    print_array2d(array, beautify, _print_char)

#endif  // ARRAY_H