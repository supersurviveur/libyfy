#include "libyfy.h"

void tests_heap() {
    MinHeap heap = heap_create(char);
    ASSERT(heap.capacity == HEAP_DEFAULT_CAPACITY);

    heap_push(&heap, 5, 'a');
    heap_push(&heap, 2, 'b');
    heap_push(&heap, 3, 'c');

    ASSERT(heap.length == 3);

    char value;
    heap_pop(&heap, &value);
    ASSERT(value == 'b');
    heap_pop(&heap, &value);
    ASSERT(value == 'c');
    heap_pop(&heap, &value);
    ASSERT(value == 'a');

    heap_free(&heap);
}