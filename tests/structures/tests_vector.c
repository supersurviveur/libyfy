#include "libyfy.h"

typedef struct {
    int a;
    int b;
} TestVector;

int compare_int(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

void square(void *a) { *(int *)a = (*(int *)a) * (*(int *)a); }


void tests_vector() {
    int *vector = vector_create(int);
    ASSERT(vector_length(vector) == 0);
    ASSERT(vector_capacity(vector) == VECTOR_DEFAULT_CAPACITY);
    ASSERT(vector_stride(vector) == sizeof(int));
    vector_push(vector, 5);
    ASSERT(vector_length(vector) == 1);
    ASSERT(vector[0] == 5);
    vector_push(vector, 10);
    vector_push(vector, 2);
    ASSERT(vector_length(vector) == 3);
    ASSERT(vector[2] == 2);
    ASSERT(vector_capacity(vector) == VECTOR_DEFAULT_CAPACITY * 2);
    int value;
    vector_pop(vector, &value);
    ASSERT(value == 2);
    ASSERT(vector_length(vector) == 2);
    vector_push(vector, 7);
    vector_push(vector, 3);
    vector_push(vector, 34);
    vector_pop_at(vector, 1, &value);
    ASSERT(value == 10);
    ASSERT(vector_length(vector) == 4);

    vector_quick_sort(vector, compare_int);
    ASSERT(vector[0] == 3);
    ASSERT(vector[1] == 5);
    ASSERT(vector[2] == 7);
    ASSERT(vector[3] == 34);

    ASSERT(vector_contains(vector, 7));
    ASSERT(!vector_contains(vector, 8));
    ASSERT(!vector_is_empty(vector));
    ASSERT(vector_index_of(vector, 7) == 2);
    ASSERT(vector_index_of(vector, 8) == -1);

    vector_map(vector, square);
    ASSERT(vector[0] == 9);
    ASSERT(vector[3] == 1156);

    int *cvector = vector_create(int);
    vector_push(cvector, 1);
    vector_push(cvector, 2);
    vector_concat(cvector, vector);
    ASSERT(vector_length(cvector) == 6);
    ASSERT(cvector[0] == 1);
    ASSERT(cvector[1] == 2);
    ASSERT(cvector[2] == 9);
    ASSERT(cvector[3] == 25);
    ASSERT(cvector[4] == 49);
    ASSERT(cvector[5] == 1156);
    vector_free(cvector);

    vector_pop(vector, &value);
    vector_pop(vector, &value);
    vector_pop(vector, &value);
    vector_pop(vector, &value);
    ASSERT(vector_is_empty(vector));

    vector_free(vector);

    float *vector2 = vector_create(float);
    vector_push(vector2, 345.45645F);
    vector_push(vector2, 45.345F);
    vector_push(vector2, 34.5F);
    ASSERT(vector2[2] == 34.5F);
    vector_free(vector2);

    TestVector *vector3 = vector_create(TestVector);
    TestVector t = {.a = 10, .b = 20};
    vector_push(vector3, t);
    ASSERT(vector_length(vector3) == 1);
    ASSERT(vector3[0].a == 10);
    ASSERT(vector3[0].b == 20);
    vector_push(vector3, ((TestVector){.a = 20, .b = 30}));
    ASSERT(vector_length(vector3) == 2);
    ASSERT(vector3[1].a == 20);
    ASSERT(vector3[1].b == 30);

    ASSERT(vector_contains(vector3, ((TestVector){.a = 20, .b = 30})));

    vector_free(vector3);

    int **vector4 = vector_create(int *);
    int *subvector = vector_create(int);
    vector_push(subvector, 1);
    vector_push(subvector, 2);
    vector_push(subvector, 3);
    vector_push(vector4, subvector);
    ASSERT(vector_length(vector4) == 1);
    ASSERT(vector_length(vector4[0]) == 3);
    ASSERT(vector4[0][2] == 3);

    int *subvector2 = vector_create(int);
    vector_push(subvector2, 4);
    vector_push(subvector2, 5);
    vector_push(subvector2, 6);
    vector_push(vector4, subvector2);

    // print_int_vector2d(vector4, false);

    vector_free(subvector);
    vector_free(subvector2);
    vector_free(vector4);
}