#define VECTOR_TYPE int
#include "structures/vector.h"
#define VECTOR_TYPE Vec_int
#include "structures/vector.h"
#define VECTOR_TYPE float
#include "structures/vector.h"

typedef struct {
    int a;
    int b;
} TestVector;

#define VECTOR_TYPE TestVector
#include "structures/vector.h"

int32_t compare_int(const int *a, const int *b) { return *a - *b; }

void square(int *a) { *a = *a * *a; }

void print_int(const int *a) { printf("%d", *a); }

void tests_vector() {
    Vec_int vector = vec_int_create();
    ASSERT(vector.length == 0);
    ASSERT(vector.capacity == VECTOR_DEFAULT_CAPACITY);
    vec_int_push(&vector, 5);
    ASSERT(vector.length == 1);
    ASSERT(vector.data[0] == 5);
    vec_int_push(&vector, 10);
    vec_int_push(&vector, 2);
    ASSERT(vector.length == 3);
    ASSERT(vector.data[2] == 2);
    ASSERT(vector.capacity == VECTOR_DEFAULT_CAPACITY * 2);
    int value;
    value = vec_int_pop(&vector);
    ASSERT(value == 2);
    ASSERT(vector.length == 2);
    vec_int_push(&vector, 7);
    vec_int_push(&vector, 3);
    vec_int_push(&vector, 34);
    value = vec_int_pop_at(&vector, 1);
    ASSERT(value == 10);
    ASSERT(vector.length == 4);

    vec_int_quick_sort(&vector, compare_int);
    ASSERT(vector.data[0] == 3);
    ASSERT(vector.data[1] == 5);
    ASSERT(vector.data[2] == 7);
    ASSERT(vector.data[3] == 34);

    ASSERT(vec_int_contains(&vector, 7));
    ASSERT(!vec_int_contains(&vector, 8));
    ASSERT(vec_int_index_of(&vector, 7) == 2);
    ASSERT(vec_int_index_of(&vector, 8) == -1);

    vec_int_map(&vector, square);
    ASSERT(vector.data[0] == 9);
    ASSERT(vector.data[3] == 1156);
    vec_int_print(&vector, true, print_int);

    Vec_int cvector = vec_int_create();
    vec_int_push(&cvector, 1);
    vec_int_push(&cvector, 2);
    vec_int_concat(&cvector, &vector);
    ASSERT(cvector.length == 6);
    ASSERT(cvector.data[0] == 1);
    ASSERT(cvector.data[1] == 2);
    ASSERT(cvector.data[2] == 9);
    ASSERT(cvector.data[3] == 25);
    ASSERT(cvector.data[4] == 49);
    ASSERT(cvector.data[5] == 1156);
    vec_int_free(&cvector);

    value = vec_int_pop(&vector);
    value = vec_int_pop(&vector);
    value = vec_int_pop(&vector);
    value = vec_int_pop(&vector);

    vec_int_free(&vector);

    Vec_float vector2 = vec_float_create();
    vec_float_push(&vector2, 345.45645F);
    vec_float_push(&vector2, 45.345F);
    vec_float_push(&vector2, 34.5F);
    ASSERT(vector2.data[2] == 34.5F);
    vec_float_free(&vector2);

    Vec_TestVector vector3 = vec_TestVector_create();
    TestVector t = {.a = 10, .b = 20};
    vec_TestVector_push(&vector3, t);
    ASSERT(vector3.length == 1);
    ASSERT(vector3.data[0].a == 10);
    ASSERT(vector3.data[0].b == 20);
    vec_TestVector_push(&vector3, ((TestVector){.a = 20, .b = 30}));
    ASSERT(vector3.length == 2);
    ASSERT(vector3.data[1].a == 20);
    ASSERT(vector3.data[1].b == 30);

    ASSERT(vec_TestVector_contains(&vector3, ((TestVector){.a = 20, .b = 30})));

    vec_TestVector_free(&vector3);

    Vec_Vec_int vector4 = vec_Vec_int_create();
    Vec_int subvector = vec_int_create();
    vec_int_push(&subvector, 1);
    vec_int_push(&subvector, 2);
    vec_int_push(&subvector, 3);
    vec_Vec_int_push(&vector4, subvector);
    ASSERT(vector4.length == 1);
    ASSERT(vector4.data[0].length == 3);
    ASSERT(vector4.data[0].data[2] == 3);

    Vec_int subvector2 = vec_int_create();
    vec_int_push(&subvector2, 4);
    vec_int_push(&subvector2, 5);
    vec_int_push(&subvector2, 6);
    vec_Vec_int_push(&vector4, subvector2);

    vec_int_print2d(&vector4, true, print_int);

    vec_int_free(&subvector);
    vec_int_free(&subvector2);
    vec_Vec_int_free(&vector4);
}