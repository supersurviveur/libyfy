#include "heap.h"

MinHeap _heap_create(size_t stride) {
    int64_t *priority = malloc(sizeof(int64_t) * HEAP_DEFAULT_CAPACITY);
    if (priority == NULL) {
        PANIC("Memory allocation failed");
    }
    void *data = malloc(stride * HEAP_DEFAULT_CAPACITY);
    if (data == NULL) {
        PANIC("Memory allocation failed");
    }
    MinHeap heap = {.capacity = HEAP_DEFAULT_CAPACITY,
                 .length = 0,
                 .stride = stride,
                 .priority = priority,
                 .data = data};
    return heap;
}

void heap_free(MinHeap *heap) {
    free(heap->priority);
    free(heap->data);
}

void _heap_push(MinHeap *heap, int64_t priority, void *value) {
    if (heap->length >= heap->capacity) {
        heap->capacity *= 2;

        heap->data = realloc(heap->data, heap->capacity * heap->stride);
        if (heap->data == NULL) {
            PANIC("Memory allocation failed");
        }
        heap->priority =
            realloc(heap->priority, heap->capacity * sizeof(int64_t));
        if (heap->priority == NULL) {
            PANIC("Memory allocation failed");
        }
    }
    memcpy((uint8_t *)heap->data + heap->stride * heap->length, value,
           heap->stride);
    heap->priority[heap->length] = priority;

    size_t i = heap->length;
    while (i > 0) {
        size_t parent = (i - 1) / 2;
        if (heap->priority[parent] <= heap->priority[i]) {
            break;
        }
        int64_t tmp_priority = heap->priority[parent];
        heap->priority[parent] = heap->priority[i];
        heap->priority[i] = tmp_priority;

        void *tmp_data = malloc(heap->stride);
        if (tmp_data == NULL) {
            PANIC("Memory allocation failed");
        }
        memcpy(tmp_data, (uint8_t *)heap->data + heap->stride * parent,
               heap->stride);
        memcpy((uint8_t *)heap->data + heap->stride * parent,
               (uint8_t *)heap->data + heap->stride * i, heap->stride);
        memcpy((uint8_t *)heap->data + heap->stride * i, tmp_data,
               heap->stride);
        free(tmp_data);

        i = parent;
    }
    heap->length++;
}

void _heap_pop(int line, const char *file, MinHeap *heap, void *value) {
    if (heap->length == 0) {
        PANIC_AT(line, file, "MinHeap is empty");
    }
    memcpy(value, heap->data, heap->stride);

    heap->length--;
    memcpy(heap->data, (uint8_t *)heap->data + heap->stride * heap->length,
           heap->stride);

    size_t i = 0;
    while (true) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        if (left >= heap->length) {
            break;
        }
        size_t min = i;
        if (heap->priority[min] > heap->priority[left]) {
            min = left;
        }
        if (right < heap->length &&
            heap->priority[min] > heap->priority[right]) {
            min = right;
        }
        if (min == i) {
            break;
        }
        int64_t tmp_priority = heap->priority[min];
        heap->priority[min] = heap->priority[i];
        heap->priority[i] = tmp_priority;

        void *tmp_data = malloc(heap->stride);
        if (tmp_data == NULL) {
            PANIC("Memory allocation failed");
        }
        memcpy(tmp_data, (uint8_t *)heap->data + heap->stride * min,
               heap->stride);
        memcpy((uint8_t *)heap->data + heap->stride * min,
               (uint8_t *)heap->data + heap->stride * i, heap->stride);
        memcpy((uint8_t *)heap->data + heap->stride * i, tmp_data,
               heap->stride);
        free(tmp_data);

        i = min;
    }
}