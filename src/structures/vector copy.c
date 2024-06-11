#include "vector copy.h"

VectorData* __get_vector_data(void* vector) {
    VectorData* data = (VectorData*)((uint8_t*)vector - VECTOR_OFFSET);
    return data;
}
void* __get_vector(void* vector) {
    return (void*)((uint8_t*)vector + VECTOR_OFFSET);
}

void* _vector_create(int stride) {
    uint8_t* vector = malloc(VECTOR_OFFSET + VECTOR_DEFAULT_CAPACITY * stride);
    if (vector == NULL) {
        PANIC("Memory allocation failed");
    }
    // Init data
    VectorData* data = (VectorData*)vector;
    data->length = 0;
    data->capacity = VECTOR_DEFAULT_CAPACITY;
    data->stride = stride;

    // Return only the vector without data
    return __get_vector(vector);
}

void vector_free(void* vector) { free(__get_vector_data(vector)); }

void* _vector_push(void* vector, void* value) {
    VectorData* data = __get_vector_data(vector);
    if (data->length >= data->capacity) {
        data->capacity *= 2;
        // Start from data to copy all the vector, not just values
        uint8_t* newVector =
            realloc(data, VECTOR_OFFSET + data->capacity * data->stride);
        if (newVector == NULL) {
            PANIC("Memory allocation failed");
        }

        data = (VectorData*)newVector;
        vector = __get_vector(newVector);
    }
    memcpy((uint8_t*)vector + data->stride * data->length, value, data->stride);
    data->length++;
    return vector;
}

void* _vector_pop(int line, const char* file, void* vector, void* value) {
    VectorData* data = __get_vector_data(vector);
    if (data->length == 0) {
        PANIC_AT(line, file, "Vector is empty");
    }
    if (value != NULL) {
        memcpy(value, ((uint8_t*)vector + (data->length - 1) * data->stride),
               data->stride);
    }
    data->length--;
    return vector;
}

void _vector_vector_pop_at(int line, const char* file, void* vector,
                           uint32_t index, void* value) {
    VectorData* data = __get_vector_data(vector);
    if (index >= data->length) {
        PANIC_AT(line, file, "Index out of bounds");
    }
    if (value != NULL) {
        memcpy(value, (uint8_t*)vector + index * data->stride, data->stride);
    }
    memmove((uint8_t*)vector + index * data->stride,
            (uint8_t*)vector + (index + 1) * data->stride,
            (data->length - index - 1) * data->stride);
    data->length--;
}

void _swap(void* a, void* b, uint32_t stride) {
    uint8_t* p;
    uint8_t* q;
    uint8_t* end = (uint8_t*)((uint64_t)a + stride);

    uint8_t t;
    for (p = a, q = b; p < end; p++, q++) {
        t = *p;
        *p = *q;
        *q = t;
    }
}

int _partition(void* vector, int (*compare)(const void*, const void*), int low,
               int high) {
    VectorData* data = __get_vector_data(vector);
    void* pivot = (uint8_t*)vector + high * data->stride;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (compare((uint8_t*)vector + j * data->stride, pivot) < 0) {
            i++;
            _swap((uint8_t*)vector + i * data->stride,
                  (uint8_t*)vector + j * data->stride, data->stride);
        }
    }
    _swap((uint8_t*)vector + (i + 1) * data->stride,
          (uint8_t*)vector + high * data->stride, data->stride);
    return i + 1;
}

/// Recursive algorithm, edit the vector in place
void _vector_quick_sort(void* vector, int (*compare)(const void*, const void*),
                        int low, int high) {
    if (low < high) {
        int pi = _partition(vector, compare, low, high);
        _vector_quick_sort(vector, compare, low, pi - 1);
        _vector_quick_sort(vector, compare, pi + 1, high);
    }
}

void vector_quick_sort(void* vector, int (*compare)(const void*, const void*)) {
    VectorData* data = __get_vector_data(vector);
    _vector_quick_sort(vector, compare, 0, data->length - 1);
}

uint32_t vector_length(void* vector) {
    VectorData* data = __get_vector_data(vector);
    return data->length;
}

uint32_t vector_capacity(void* vector) {
    VectorData* data = __get_vector_data(vector);
    return data->capacity;
}

uint32_t vector_stride(void* vector) {
    VectorData* data = __get_vector_data(vector);
    return data->stride;
}

void _print_int(const void* a) { printf("%d", *(const int*)a); }
void _print_float(const void* a) { printf("%f", *(const float*)a); }
void _print_double(const void* a) { printf("%f", *(const double*)a); }
void _print_char(const void* a) { printf("%c", *(const char*)a); }

void _print_vector(void* vector, bool beautify, bool logger,
                   void (*print)(const void*), int line, const char* file) {
    VectorData* data = __get_vector_data(vector);
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
        print((const uint8_t*)vector + i * data->stride);
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

void _print_vector2d(void* vector, bool beautify,
                     void (*print)(const void*), int line, const char* file) {
    VectorData* data = __get_vector_data(vector);
    INFO_NO_NL_AT(line, file, "Length: %d -> ", data->length);
    printf("[");
    if (beautify) {
        printf("\n");
    }
    for (int i = 0; i < (int)data->length; i++) {
        if (beautify) {
            printf("  ");
        }
        print_vector_no_logger(
            *(void**)((uint8_t*)vector + i * data->stride), false,
            print);
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

bool vector_is_empty(void* vector) {
    VectorData* data = __get_vector_data(vector);
    return data->length == 0;
}

bool _vector_contains(void* vector, void* value) {
    VectorData* data = __get_vector_data(vector);
    for (int i = 0; i < (int)data->length; i++) {
        if (memcmp((uint8_t*)vector + i * data->stride, value, data->stride) ==
            0) {
            return true;
        }
    }
    return false;
}

int32_t _vector_index_of(void* vector, void* value) {
    VectorData* data = __get_vector_data(vector);
    for (int i = 0; i < (int)data->length; i++) {
        if (memcmp((uint8_t*)vector + i * data->stride, value, data->stride) ==
            0) {
            return i;
        }
    }
    return -1;
}

void vector_map(void* vector, void (*map)(void*)) {
    VectorData* data = __get_vector_data(vector);
    for (int i = 0; i < (int)data->length; i++) {
        map((uint8_t*)vector + i * data->stride);
    }
}

void* _vector_concat(void* vector, void* other) {
    VectorData* data = __get_vector_data(vector);
    VectorData* otherData = __get_vector_data(other);
    if (data->stride != otherData->stride) {
        PANIC("Vectors have different types");
    }
    for (int i = 0; i < (int)otherData->length; i++) {
        vector = _vector_push(vector, (uint8_t*)other + i * otherData->stride);
    }
    return vector;
}