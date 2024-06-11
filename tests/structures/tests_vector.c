#define VECTOR_TYPE int
#include "structures/vector.h"
#define VECTOR_TYPE Vector_int
#include "structures/vector.h"
#define VECTOR_TYPE float
#include "structures/vector.h"

typedef struct {
    int a;
    int b;
} TestVector;

#define VECTOR_TYPE TestVector
#include "structures/vector.h"

int32_t compare_int(const int *a, const int *b) {
    return (*(const int *)a - *(const int *)b);
}

void square(int *a) { *a = (*(a) * (*a)); }

void print_int(const int *a) {
    printf("%d", *a);
}

void tests_vector() {
    Vector_int vector = vector_int_create();
    ASSERT(vector.length == 0);
    ASSERT(vector.capacity == VECTOR_DEFAULT_CAPACITY);
    vector_int_push(&vector, 5);
    ASSERT(vector.length == 1);
    ASSERT(vector.data[0] == 5);
    vector_int_push(&vector, 10);
    vector_int_push(&vector, 2);
    ASSERT(vector.length == 3);
    ASSERT(vector.data[2] == 2);
    ASSERT(vector.capacity == VECTOR_DEFAULT_CAPACITY * 2);
    int value;
    vector_int_pop(&vector, &value);
    ASSERT(value == 2);
    ASSERT(vector.length == 2);
    vector_int_push(&vector, 7);
    vector_int_push(&vector, 3);
    vector_int_push(&vector, 34);
    vector_int_pop_at(&vector, 1, &value);
    ASSERT(value == 10);
    ASSERT(vector.length == 4);

    vector_int_quick_sort(&vector, compare_int);
    ASSERT(vector.data[0] == 3);
    ASSERT(vector.data[1] == 5);
    ASSERT(vector.data[2] == 7);
    ASSERT(vector.data[3] == 34);

    ASSERT(vector_int_contains(&vector, 7));
    ASSERT(!vector_int_contains(&vector, 8));
    ASSERT(vector_int_index_of(&vector, 7) == 2);
    ASSERT(vector_int_index_of(&vector, 8) == -1);

    vector_int_map(&vector, square);
    ASSERT(vector.data[0] == 9);
    ASSERT(vector.data[3] == 1156);
    // vector_int_print(&vector, true, print_int);

    Vector_int cvector = vector_int_create();
    vector_int_push(&cvector, 1);
    vector_int_push(&cvector, 2);
    vector_int_concat(&cvector, &vector);
    ASSERT(cvector.length == 6);
    ASSERT(cvector.data[0] == 1);
    ASSERT(cvector.data[1] == 2);
    ASSERT(cvector.data[2] == 9);
    ASSERT(cvector.data[3] == 25);
    ASSERT(cvector.data[4] == 49);
    ASSERT(cvector.data[5] == 1156);
    vector_int_free(&cvector);

    vector_int_pop(&vector, &value);
    vector_int_pop(&vector, &value);
    vector_int_pop(&vector, &value);
    vector_int_pop(&vector, &value);

    vector_int_free(&vector);

    Vector_float vector2 = vector_float_create();
    vector_float_push(&vector2, 345.45645F);
    vector_float_push(&vector2, 45.345F);
    vector_float_push(&vector2, 34.5F);
    ASSERT(vector2.data[2] == 34.5F);
    vector_float_free(&vector2);

    Vector_TestVector vector3 = vector_TestVector_create();
    TestVector t = {.a = 10, .b = 20};
    vector_TestVector_push(&vector3, t);
    ASSERT(vector3.length == 1);
    ASSERT(vector3.data[0].a == 10);
    ASSERT(vector3.data[0].b == 20);
    vector_TestVector_push(&vector3, ((TestVector){.a = 20, .b = 30}));
    ASSERT(vector3.length == 2);
    ASSERT(vector3.data[1].a == 20);
    ASSERT(vector3.data[1].b == 30);

    ASSERT(vector_TestVector_contains(&vector3, ((TestVector){.a = 20, .b = 30})));

    vector_TestVector_free(&vector3);

    Vector_Vector_int vector4 = vector_Vector_int_create();
    Vector_int subvector = vector_int_create();
    vector_int_push(&subvector, 1);
    vector_int_push(&subvector, 2);
    vector_int_push(&subvector, 3);
    vector_Vector_int_push(&vector4, subvector);
    ASSERT(vector4.length == 1);
    ASSERT(vector4.data[0].length == 3);
    ASSERT(vector4.data[0].data[2] == 3);

    Vector_int subvector2 = vector_int_create();
    vector_int_push(&subvector2, 4);
    vector_int_push(&subvector2, 5);
    vector_int_push(&subvector2, 6);
    vector_Vector_int_push(&vector4, subvector2);

    vector_int_print2d(&vector4, true, print_int);

    vector_int_free(&subvector);
    vector_int_free(&subvector2);
    vector_Vector_int_free(&vector4);
}