#pragma once

#include <malloc.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../exception.h"

#define HEAP_DEFAULT_CAPACITY 2

typedef struct {
    size_t capacity;
    size_t length;
    size_t stride;
    int64_t *priority;
    void *data;
} MinHeap;

// private functions
MinHeap _heap_create(size_t stride);
void _heap_push(MinHeap *heap, int64_t priority, void *value);

#define heap_create(type) _heap_create(sizeof(type))

void heap_free(MinHeap *heap);

/// @brief Push a value to the heap
/// @param heap pointer to the heap
/// @param priority The value's priority
/// @param value value to push
#define heap_push(heap, priority, value)  \
    {                                     \
        typeof(value) tmp = value;        \
        _heap_push(heap, priority, &tmp); \
    }

/// @brief Pop a value from the heap
/// @param heap pointer to the heap
/// @param value pointer to store the value
void heap_pop(MinHeap *heap, void *value);
