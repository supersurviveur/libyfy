#include "libyfy.h"

typedef struct {
    int a;
    int b;
} TestHashtable;

uint32_t test_hashtable_hash(const void *key) {
    return ((const TestHashtable *)key)->a;
}

void tests_hashtable() {
    HashTable *table = hashtable_create(int, int, int_hash);
    hashtable_set(table, 1, 2);
    hashtable_set(table, 2, 3);
    hashtable_set(table, 3, 4);
    ASSERT(hashtable_get(table, 1, int) == 2);
    ASSERT(hashtable_get(table, 2, int) == 3);
    ASSERT(hashtable_get(table, 3, int) == 4);
    ASSERT(hashtable_contains(table, 1));
    ASSERT(hashtable_contains(table, 2));
    ASSERT(hashtable_contains(table, 3));
    ASSERT(!hashtable_contains(table, 4));

    hashtable_set(table, 2, 4);
    ASSERT(hashtable_get(table, 2, int) == 4);
    ASSERT(hashtable_get(table, 3, int) == 4);
    ASSERT(hashtable_contains(table, 2));

    hashtable_delete(table, 2);
    ASSERT(!hashtable_contains(table, 2));
    ASSERT(hashtable_contains(table, 3));

    hashtable_free(table);

    table = hashtable_create(TestHashtable, TestHashtable, test_hashtable_hash);
    hashtable_set(table, ((TestHashtable){1, 2}), ((TestHashtable){3, 4}));
    hashtable_set(table, ((TestHashtable){2, 3}), ((TestHashtable){4, 5}));
    hashtable_set(table, ((TestHashtable){3, 4}), ((TestHashtable){5, 6}));
    ASSERT(hashtable_get(table, ((TestHashtable){1, 2}), TestHashtable).a == 3);
    ASSERT(hashtable_get(table, ((TestHashtable){2, 3}), TestHashtable).a == 4);
    ASSERT(hashtable_get(table, ((TestHashtable){3, 4}), TestHashtable).a == 5);
    ASSERT(hashtable_get(table, ((TestHashtable){1, 2}), TestHashtable).b == 4);
    ASSERT(hashtable_get(table, ((TestHashtable){2, 3}), TestHashtable).b == 5);
    ASSERT(hashtable_get(table, ((TestHashtable){3, 4}), TestHashtable).b == 6);
    ASSERT(hashtable_contains(table, ((TestHashtable){1, 2})));
    ASSERT(hashtable_contains(table, ((TestHashtable){2, 3})));
    ASSERT(hashtable_contains(table, ((TestHashtable){3, 4})));

    // Try conflicting hash
    hashtable_set(table, ((TestHashtable){1, 3}), ((TestHashtable){10, 11}));
    ASSERT(hashtable_get(table, ((TestHashtable){1, 2}), TestHashtable).a == 3);
    ASSERT(hashtable_get(table, ((TestHashtable){1, 3}), TestHashtable).a ==
           10);
    ASSERT(hashtable_get(table, ((TestHashtable){1, 2}), TestHashtable).b == 4);
    ASSERT(hashtable_get(table, ((TestHashtable){1, 3}), TestHashtable).b ==
           11);

    ASSERT(hashtable_contains(table, ((TestHashtable){1, 2})));
    ASSERT(hashtable_contains(table, ((TestHashtable){1, 3})));

    hashtable_free(table);

    // Test others hash functions
    table = hashtable_create(char *, int, cstr_hash);
    hashtable_set(table, &"a", 1);

    ASSERT(hashtable_get(table, &"a", int) == 1);
    ASSERT(hashtable_contains(table, &"a"));
    ASSERT(!hashtable_contains(table, &"b"));
    hashtable_set(table, &"ab", 2);
    ASSERT(hashtable_get(table, &"ab", int) == 2);
    ASSERT(hashtable_get(table, &"a", int) == 1);
    ASSERT(hashtable_contains(table, &"ab"));
    ASSERT(!hashtable_contains(table, &"b"));

    hashtable_delete(table, &"a");
    ASSERT(!hashtable_contains(table, &"a"));
    ASSERT(hashtable_contains(table, &"ab"));

    hashtable_free(table);
}
