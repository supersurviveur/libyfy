#include "../src/array.h"

typedef struct {
    int a;
    int b;
} TestArray;

int compare_int(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void square(void *a) { *(int *)a = (*(int *)a) * (*(int *)a); }


void tests_array() {
    int *array = array_create(int);
    ASSERT(array_length(array) == 0);
    ASSERT(array_capacity(array) == ARRAY_DEFAULT_CAPACITY);
    ASSERT(array_type_size(array) == sizeof(int));
    array_push(array, 5);
    ASSERT(array_length(array) == 1);
    ASSERT(array[0] == 5);
    array_push(array, 10);
    array_push(array, 2);
    ASSERT(array_length(array) == 3);
    ASSERT(array[2] == 2);
    ASSERT(array_capacity(array) == ARRAY_DEFAULT_CAPACITY * 2);
    int value;
    array_pop(array, &value);
    ASSERT(value == 2);
    ASSERT(array_length(array) == 2);
    array_push(array, 7);
    array_push(array, 3);
    array_push(array, 34);
    array_pop_at(array, 1, &value);
    ASSERT(value == 10);
    ASSERT(array_length(array) == 4);

    array_quick_sort(array, compare_int);
    ASSERT(array[0] == 3);
    ASSERT(array[1] == 5);
    ASSERT(array[2] == 7);
    ASSERT(array[3] == 34);

    ASSERT(array_contains(array, 7));
    ASSERT(!array_contains(array, 8));
    ASSERT(!array_is_empty(array));
    ASSERT(array_index_of(array, 7) == 2);
    ASSERT(array_index_of(array, 8) == -1);

    array_map(array, square);
    ASSERT(array[0] == 9);
    ASSERT(array[3] == 1156);

    int *carray = array_create(int);
    array_push(carray, 1);
    array_push(carray, 2);
    array_concat(carray, array);
    ASSERT(array_length(carray) == 6);
    ASSERT(carray[0] == 1);
    ASSERT(carray[1] == 2);
    ASSERT(carray[2] == 9);
    ASSERT(carray[3] == 25);
    ASSERT(carray[4] == 49);
    ASSERT(carray[5] == 1156);
    array_free(carray);

    array_pop(array, &value);
    array_pop(array, &value);
    array_pop(array, &value);
    array_pop(array, &value);
    ASSERT(array_is_empty(array));

    array_free(array);

    float *array2 = array_create(float);
    array_push(array2, 345.45645F);
    array_push(array2, 45.345F);
    array_push(array2, 34.5F);
    ASSERT(array2[2] == 34.5F);
    array_free(array2);

    TestArray *array3 = array_create(TestArray);
    TestArray t = {.a = 10, .b = 20};
    array_push(array3, t);
    ASSERT(array_length(array3) == 1);
    ASSERT(array3[0].a == 10);
    ASSERT(array3[0].b == 20);
    array_push(array3, ((TestArray){.a = 20, .b = 30}));
    ASSERT(array_length(array3) == 2);
    ASSERT(array3[1].a == 20);
    ASSERT(array3[1].b == 30);

    ASSERT(array_contains(array3, ((TestArray){.a = 20, .b = 30})));

    array_free(array3);

    int **array4 = array_create(int *);
    int *subarray = array_create(int);
    array_push(subarray, 1);
    array_push(subarray, 2);
    array_push(subarray, 3);
    array_push(array4, subarray);
    ASSERT(array_length(array4) == 1);
    ASSERT(array_length(array4[0]) == 3);
    ASSERT(array4[0][2] == 3);

    int *subarray2 = array_create(int);
    array_push(subarray2, 4);
    array_push(subarray2, 5);
    array_push(subarray2, 6);
    array_push(array4, subarray2);

    // print_int_array2d(array4, false);

    array_free(subarray);
    array_free(subarray2);
    array_free(array4);
}