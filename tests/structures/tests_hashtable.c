#define KEY_TYPE int
#define VALUE_TYPE int
#include "structures/hashmap.h"

typedef char *charp;
#define KEY_TYPE charp
#define VALUE_TYPE int
#include "structures/hashmap.h"

typedef struct {
    int a;
    int b;
} TestHashmap;

#define KEY_TYPE TestHashmap
#define VALUE_TYPE TestHashmap
#include "structures/hashmap.h"

uint32_t test_hashmap_hash(TestHashmap key) { return key.a; }

bool test_hashmap_comp(TestHashmap a, TestHashmap b) {
    return a.a == b.a && a.b == b.b;
}

bool char_comp(char *a, char *b) { return strcmp(a, b) == 0; }

bool int_comp(int a, int b) { return a == b; }

void tests_hashmap() {
    HashMap_int_int map = hashmap_int_int_create(int_hash, int_comp);
    hashmap_int_int_set(&map, 1, 2);
    hashmap_int_int_set(&map, 2, 3);
    hashmap_int_int_set(&map, 3, 4);
    ASSERT(*hashmap_int_int_get(&map, 1) == 2);
    ASSERT(*hashmap_int_int_get(&map, 2) == 3);
    ASSERT(*hashmap_int_int_get(&map, 3) == 4);
    ASSERT(hashmap_int_int_contains(&map, 1));
    ASSERT(hashmap_int_int_contains(&map, 2));
    ASSERT(hashmap_int_int_contains(&map, 3));
    ASSERT(!hashmap_int_int_contains(&map, 4));

    hashmap_int_int_set(&map, 2, 4);
    ASSERT(*hashmap_int_int_get(&map, 2) == 4);
    ASSERT(*hashmap_int_int_get(&map, 3) == 4);
    ASSERT(hashmap_int_int_contains(&map, 2));

    hashmap_int_int_delete(&map, 2);
    ASSERT(!hashmap_int_int_contains(&map, 2));
    ASSERT(hashmap_int_int_contains(&map, 3));

    hashmap_int_int_free(&map);

    HashMap_TestHashmap_TestHashmap map2 =
        hashmap_TestHashmap_TestHashmap_create(test_hashmap_hash,
                                               test_hashmap_comp);
    hashmap_TestHashmap_TestHashmap_set(&map2, ((TestHashmap){1, 2}),
                                        ((TestHashmap){3, 4}));
    hashmap_TestHashmap_TestHashmap_set(&map2, ((TestHashmap){2, 3}),
                                        ((TestHashmap){4, 5}));
    hashmap_TestHashmap_TestHashmap_set(&map2, ((TestHashmap){3, 4}),
                                        ((TestHashmap){5, 6}));
    ASSERT(
        hashmap_TestHashmap_TestHashmap_get(&map2, ((TestHashmap){1, 2}))->a ==
        3);
    ASSERT(
        hashmap_TestHashmap_TestHashmap_get(&map2, ((TestHashmap){2, 3}))->a ==
        4);
    ASSERT(
        hashmap_TestHashmap_TestHashmap_get(&map2, ((TestHashmap){3, 4}))->a ==
        5);
    ASSERT(
        hashmap_TestHashmap_TestHashmap_get(&map2, ((TestHashmap){1, 2}))->b ==
        4);
    ASSERT(
        hashmap_TestHashmap_TestHashmap_get(&map2, ((TestHashmap){2, 3}))->b ==
        5);
    ASSERT(
        hashmap_TestHashmap_TestHashmap_get(&map2, ((TestHashmap){3, 4}))->b ==
        6);
    ASSERT(
        hashmap_TestHashmap_TestHashmap_contains(&map2, ((TestHashmap){1, 2})));
    ASSERT(
        hashmap_TestHashmap_TestHashmap_contains(&map2, ((TestHashmap){2, 3})));
    ASSERT(
        hashmap_TestHashmap_TestHashmap_contains(&map2, ((TestHashmap){3, 4})));

    // Try conflicting hash
    hashmap_TestHashmap_TestHashmap_set(&map2, ((TestHashmap){1, 3}),
                                        ((TestHashmap){10, 11}));
    ASSERT(
        hashmap_TestHashmap_TestHashmap_get(&map2, ((TestHashmap){1, 2}))->a ==
        3);
    ASSERT(
        hashmap_TestHashmap_TestHashmap_get(&map2, ((TestHashmap){1, 3}))->a ==
        10);
    ASSERT(
        hashmap_TestHashmap_TestHashmap_get(&map2, ((TestHashmap){1, 2}))->b ==
        4);
    ASSERT(
        hashmap_TestHashmap_TestHashmap_get(&map2, ((TestHashmap){1, 3}))->b ==
        11);

    ASSERT(
        hashmap_TestHashmap_TestHashmap_contains(&map2, ((TestHashmap){1, 2})));
    ASSERT(
        hashmap_TestHashmap_TestHashmap_contains(&map2, ((TestHashmap){1, 3})));

    hashmap_TestHashmap_TestHashmap_free(&map2);

    // Test others hash functions
    HashMap_charp_int map3 = hashmap_charp_int_create(cstr_hash, char_comp);
    hashmap_charp_int_set(&map3, "a", 1);

    ASSERT(*hashmap_charp_int_get(&map3, "a") == 1);
    ASSERT(hashmap_charp_int_contains(&map3, "a"));
    ASSERT(!hashmap_charp_int_contains(&map3, "b"));
    hashmap_charp_int_set(&map3, "ab", 2);
    ASSERT(*hashmap_charp_int_get(&map3, "ab") == 2);
    ASSERT(*hashmap_charp_int_get(&map3, "a") == 1);
    ASSERT(hashmap_charp_int_contains(&map3, "ab"));
    ASSERT(!hashmap_charp_int_contains(&map3, "b"));

    hashmap_charp_int_delete(&map3, "a");
    ASSERT(!hashmap_charp_int_contains(&map3, "a"));
    ASSERT(hashmap_charp_int_contains(&map3, "ab"));

    hashmap_charp_int_free(&map3);
};