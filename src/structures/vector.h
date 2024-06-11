/// Resizable array of any type.

#define VECTOR_DEFAULT_CAPACITY 2

#ifndef VECTOR_TYPE
#error "VECTOR_TYPE must be defined"
#else

#define TYPE__(pred, name, VECTOR) pred##VECTOR##name
#define TYPE_(pred, name, VECTOR) TYPE__(pred, name, VECTOR)
#define TYPE(name) TYPE_(vector_, name, VECTOR_TYPE)
#define STYPE TYPE_(Vector_, , VECTOR_TYPE)

#include <malloc.h>
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "../exception.h"
#include "../logging.h"

/// @brief Struct to store the vector data, stored before the vector pointer
/// @param length length of the vector
/// @param capacity current capacity of the vector
typedef struct {
    size_t length;
    size_t capacity;
    VECTOR_TYPE *data;
} STYPE;

/// @brief Create an empty vector
/// @return - the vector
STYPE TYPE(_create)() {
    VECTOR_TYPE *data = malloc(VECTOR_DEFAULT_CAPACITY * sizeof(VECTOR_TYPE));
    if (data == NULL) {
        PANIC("Memory allocation failed");
    }

    STYPE vector = {
        .capacity = VECTOR_DEFAULT_CAPACITY, .data = data, .length = 0};

    return vector;
}

/// @brief Push a value to the vector
/// @param vector pointer to the vector
/// @param value value to push
void TYPE(_push)(STYPE *vector, VECTOR_TYPE value) {
    if (vector->length >= vector->capacity) {
        vector->capacity *= 2;

        VECTOR_TYPE *newData =
            realloc(vector->data, vector->capacity * sizeof(VECTOR_TYPE));
        if (newData == NULL) {
            PANIC("Memory allocation failed");
        }

        vector->data = newData;
    }
    memcpy(vector->data + vector->length, &value, sizeof(VECTOR_TYPE));
    vector->length++;
}

/// @brief Free the vector
/// @param vector pointer to the vector
void TYPE(_free)(STYPE *vector) { free(vector->data); }

/// @brief Pop the last value from the vector
/// @param vector pointer to the vector
/// @param value pointer to store the value
void TYPE(_pop)(STYPE *vector, VECTOR_TYPE *value) {
    if (vector->length == 0) {
        PANIC("Vector is empty");
    }
    if (value != NULL) {
        memcpy(value, (vector->data + (vector->length - 1)),
               sizeof(VECTOR_TYPE));
    }
    vector->length--;
}

/// @brief Pop a value from the vector at a specific index
/// @param vector pointer to the vector
/// @param index index to pop
/// @param value pointer to store the value
void TYPE(_pop_at)(STYPE *vector, size_t index, VECTOR_TYPE *value) {
    if (vector->length <= index) {
        PANIC("Index out of bounds");
    }
    if (value != NULL) {
        memcpy(value, (vector->data + index), sizeof(VECTOR_TYPE));
    }
    memmove(vector->data + index, vector->data + (index + 1),
            (vector->length - index - 1) * sizeof(VECTOR_TYPE));
    vector->length--;
}

void TYPE(_print_internal)(STYPE *vector, bool beautify, bool logger,
                           void (*print)(const VECTOR_TYPE *)) {
    if (logger) {
        INFO_NO_NL("Length: %d -> ", vector->length);
    }
    printf("[");
    if (beautify) {
        printf("\n");
    }
    for (size_t i = 0; i < vector->length; i++) {
        if (beautify) {
            printf("  ");
        }
        print(vector->data + i);
        if (i != vector->length - 1) {
            if (beautify) {
                printf(",\n");
            } else {
                printf(", ");
            }
        }
    }
    if (beautify) {
        printf("\n");
    }
    printf("]");
    if (logger) {
        printf("\n");
    }
}

/// @brief Print a vector
/// @param vector pointer to the vector
/// @param beautify if true, print the vector in a beautified way
/// @param print function to print the elements
void TYPE(_print)(STYPE *vector, bool beautify,
                  void (*print)(const VECTOR_TYPE *)) {
    TYPE(_print_internal)(vector, beautify, true, print);
}

/// @brief Print a 2D vector, not stable !
/// @param vector pointer to the vector
/// @param beautify if true, print the vector in a beautified way
/// @param print function to print the elements
void TYPE(_print2d)(void *vector, bool beautify,
                    void (*print)(const VECTOR_TYPE *)) {
    STYPE *vect = (STYPE *)vector;
    INFO_NO_NL("Length: %d -> ", vect->length);
    printf("[");
    if (beautify) {
        printf("\n");
    }
    for (size_t i = 0; i < vect->length; i++) {
        if (beautify) {
            printf("  ");
        }
        TYPE(_print_internal)
        ((STYPE *)vect->data + i, false, false, print);
        if (i != vect->length - 1) {
            if (beautify) {
                printf(",\n");
            } else {
                printf(", ");
            }
        }
    }
    if (beautify) {
        printf("\n");
    }
    printf("]\n");
}

/// @brief Check if the vector contains a value
/// @param vector pointer to the vector
/// @param value value to check
bool TYPE(_contains)(STYPE *vector, VECTOR_TYPE value) {
    for (size_t i = 0; i < vector->length; i++) {
        if (memcmp(vector->data + i, &value, sizeof(VECTOR_TYPE)) == 0) {
            return true;
        }
    }
    return false;
};

/// @brief Get the index of a value in the vector
/// @param vector pointer to the vector
/// @param value value to check
/// @return `int32_t` - index of the value, -1 if not found
int32_t TYPE(_index_of)(STYPE *vector, VECTOR_TYPE value) {
    for (size_t i = 0; i < vector->length; i++) {
        if (memcmp(vector->data + i, &value, sizeof(VECTOR_TYPE)) == 0) {
            return i;
        }
    }
    return -1;
};

/// @brief Concatenate an vector to another
/// @param vector pointer to the vector
/// @param other pointer to the other vector
void TYPE(_concat)(STYPE *vector, STYPE *other) {
    for (size_t i = 0; i < other->length; i++) {
        TYPE(_push)(vector, *(other->data + i));
    }
};

/// @brief Map the vector using a function
/// @param vector pointer to the vector
/// @param map function to map the elements
void TYPE(_map)(STYPE *vector, void (*map)(VECTOR_TYPE *)) {
    for (size_t i = 0; i < vector->length; i++) {
        map(vector->data + i);
    }
};

int64_t TYPE(_partition)(STYPE *vector,
                         int32_t (*compare)(const VECTOR_TYPE *,
                                            const VECTOR_TYPE *),
                         int64_t low, int64_t high) {
    void *pivot = vector->data + high;
    int64_t i = low - 1;
    for (int64_t j = low; j < high; j++) {
        if (compare(vector->data + j, pivot) < 0) {
            i++;
            VECTOR_TYPE tmp = vector->data[i];
            vector->data[i] = vector->data[j];
            vector->data[j] = tmp;
        }
    }
    VECTOR_TYPE tmp = vector->data[i + 1];
    vector->data[i + 1] = vector->data[high];
    vector->data[high] = tmp;
    return i + 1;
}

/// Recursive algorithm, edit the vector in place
void TYPE(_quick_sort_)(STYPE *vector,
                        int32_t (*compare)(const VECTOR_TYPE *,
                                           const VECTOR_TYPE *),
                        int64_t low, int64_t high) {
    if (low < high) {
        int64_t pi = TYPE(_partition)(vector, compare, low, high);
        TYPE(_quick_sort_)(vector, compare, low, pi - 1);
        TYPE(_quick_sort_)(vector, compare, pi + 1, high);
    }
}

/// @brief Sort the vector using quick sort
/// @param vector pointer to the vector
/// @param compare function to compare the elements
void TYPE(_quick_sort)(STYPE *vector, int32_t (*compare)(const VECTOR_TYPE *,
                                                         const VECTOR_TYPE *)) {
    TYPE(_quick_sort_)(vector, compare, 0, vector->length - 1);
}

#undef VECTOR_TYPE
#endif