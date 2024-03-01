#include "array.h"

ArrayData* __get_array_data(const void* array) {
    ArrayData* data = (ArrayData*)((uint8_t*)array - ARRAY_OFFSET);
    return data;
}
void* __get_array(void* array) {
    return (void*)((uint8_t*)array + ARRAY_OFFSET);
}

void* _array_create(int type_size) {
    uint8_t* array = malloc(ARRAY_OFFSET + ARRAY_DEFAULT_CAPACITY * type_size);
    if (array == NULL) {
        PANIC("Memory allocation failed");
    }
    // Init data
    ArrayData* data = (ArrayData*)array;
    data->length = 0;
    data->capacity = ARRAY_DEFAULT_CAPACITY;
    data->type_size = type_size;

    // Return only the array without data
    return __get_array(array);
}

void array_free(void* array) { free(__get_array_data(array)); }

void* _array_push(void* array, void* value) {
    ArrayData* data = __get_array_data(array);
    if (data->length >= data->capacity) {
        data->capacity *= 2;
        // Start from data to copy all the array, not just values
        uint8_t* newArray =
            realloc(data, ARRAY_OFFSET + data->capacity * data->type_size);
        if (newArray == NULL) {
            PANIC("Memory allocation failed");
        }

        data = (ArrayData*)newArray;
        array = __get_array(newArray);
    }
    memcpy(array + data->type_size * data->length, value, data->type_size);
    data->length++;
    return array;
}

void* _array_pop(int line, const char* file, void* array, void* value) {
    ArrayData* data = __get_array_data(array);
    if (data->length == 0) {
        PANIC_AT(line, file, "Array is empty");
    }
    if (value != NULL) {
        memcpy(value, ((uint8_t*)array + (data->length - 1) * data->type_size),
               data->type_size);
    }
    data->length--;
    return array;
}

void _array_array_pop_at(int line, const char* file, void* array,
                         uint32_t index, void* value) {
    ArrayData* data = __get_array_data(array);
    if (index >= data->length) {
        PANIC_AT(line, file, "Index out of bounds");
    }
    if (value != NULL) {
        memcpy(value, (uint8_t*)array + index * data->type_size,
               data->type_size);
    }
    memmove((uint8_t*)array + index * data->type_size,
            (uint8_t*)array + (index + 1) * data->type_size,
            (data->length - index - 1) * data->type_size);
    data->length--;
}

void _swap(void* a, void* b, uint32_t type_size) {
    uint8_t* p;
    uint8_t* q;
    uint8_t* end = (uint8_t*)((uint64_t)a + type_size);

    uint8_t t;
    for (p = a, q = b; p < end; p++, q++) {
        t = *p;
        *p = *q;
        *q = t;
    }
}

int _partition(void* array, int (*compare)(const void*, const void*), int low,
               int high) {
    ArrayData* data = __get_array_data(array);
    void* pivot = (uint8_t*)array + high * data->type_size;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (compare((uint8_t*)array + j * data->type_size, pivot) < 0) {
            i++;
            _swap((uint8_t*)array + i * data->type_size,
                  (uint8_t*)array + j * data->type_size, data->type_size);
        }
    }
    _swap((uint8_t*)array + (i + 1) * data->type_size,
          (uint8_t*)array + high * data->type_size, data->type_size);
    return i + 1;
}

/// Recursive algorithm, edit the array in place
void _array_quick_sort(void* array, int (*compare)(const void*, const void*),
                       int low, int high) {
    if (low < high) {
        int pi = _partition(array, compare, low, high);
        _array_quick_sort(array, compare, low, pi - 1);
        _array_quick_sort(array, compare, pi + 1, high);
    }
}

void array_quick_sort(void* array, int (*compare)(const void*, const void*)) {
    ArrayData* data = __get_array_data(array);
    _array_quick_sort(array, compare, 0, data->length - 1);
}

uint32_t array_length(void* array) {
    ArrayData* data = __get_array_data(array);
    return data->length;
}

uint32_t array_capacity(void* array) {
    ArrayData* data = __get_array_data(array);
    return data->capacity;
}

uint32_t array_type_size(void* array) {
    ArrayData* data = __get_array_data(array);
    return data->type_size;
}

void _print_int(const void* a) { printf("%d", *(int*)a); }
void _print_float(const void* a) { printf("%f", *(float*)a); }
void _print_double(const void* a) { printf("%f", *(double*)a); }
void _print_char(const void* a) { printf("%c", *(char*)a); }

void _print_array(const void* array, bool beautify, bool logger,
                  void (*print)(const void*), int line, const char* file) {
    ArrayData* data = __get_array_data(array);
    if (logger) {
        INFO_NO_NL_AT(line, file, "Length: %d -> ", data->length);
    }
    printf("[");
    if (beautify) {
        printf("\n");
    }
    for (int i = 0; i < (int)data->length; i++) {
        if (beautify) {
            printf("  ");
        }
        print((uint8_t*)array + i * data->type_size);
        if (i != (int)data->length - 1) {
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

void _print_array2d(const void* array, bool beautify,
                    void (*print)(const void*), int line, const char* file) {
    ArrayData* data = __get_array_data(array);
    INFO_NO_NL_AT(line, file, "Length: %d -> ", data->length);
    printf("[");
    if (beautify) {
        printf("\n");
    }
    for (int i = 0; i < (int)data->length; i++) {
        if (beautify) {
            printf("  ");
        }
        print_array_no_logger(*(void**)((uint8_t*)array + i * data->type_size),
                              false, print);
        if (i != (int)data->length - 1) {
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

bool array_is_empty(void* array) {
    ArrayData* data = __get_array_data(array);
    return data->length == 0;
}

bool _array_contains(void* array, void* value) {
    ArrayData* data = __get_array_data(array);
    for (int i = 0; i < (int)data->length; i++) {
        if (memcmp((uint8_t*)array + i * data->type_size, value,
                   data->type_size) == 0) {
            return true;
        }
    }
    return false;
}

int32_t _array_index_of(void* array, void* value) {
    ArrayData* data = __get_array_data(array);
    for (int i = 0; i < (int)data->length; i++) {
        if (memcmp((uint8_t*)array + i * data->type_size, value,
                   data->type_size) == 0) {
            return i;
        }
    }
    return -1;
}

void array_map(void* array, void (*map)(void*)) {
    ArrayData* data = __get_array_data(array);
    for (int i = 0; i < (int)data->length; i++) {
        map((uint8_t*)array + i * data->type_size);
    }
}

void* _array_concat(void* array, void* other) {
    ArrayData* data = __get_array_data(array);
    ArrayData* otherData = __get_array_data(other);
    if (data->type_size != otherData->type_size) {
        PANIC("Arrays have different types");
    }
    for (int i = 0; i < (int)otherData->length; i++) {
        array = _array_push(array, (uint8_t*)other + i * otherData->type_size);
    }
    return array;
}