#ifndef KEY_TYPE
#error "KEY_TYPE must be defined"
#else

#ifndef VALUE_TYPE
#error "VALUE_TYPE must be defined"
#else

#include "utils.h"

#define TYPE__(pred, name, a, b) CONCAT(pred, a##_##b, name)
#define TYPE_(pred, name, a, b) TYPE__(pred, name, a, b)
#define TYPE(name) TYPE_(hashmap_, name, KEY_TYPE, VALUE_TYPE)
#define TS_TYPE TYPE_(HashMap_, , KEY_TYPE, VALUE_TYPE)
#define NS_TYPE TYPE_(HashNode_, , KEY_TYPE, VALUE_TYPE)

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../exception.h"
#include "linkedlist.h"

#define HASHTABLE_DEFAULT_CAPACITY 2

typedef struct {
    KEY_TYPE key;
    VALUE_TYPE value;
} NS_TYPE;

// Hashtable using linked list
typedef struct {
    uint32_t length;
    uint32_t capacity;
    uint32_t (*hash)(KEY_TYPE);
    bool (*comp)(KEY_TYPE, KEY_TYPE);
    LinkedList **buckets;
} TS_TYPE;

/// @brief Create an empty hashtable
/// @param key_type type of the key
/// @param value_type type of the value
/// @param hash hash function for the key
TS_TYPE TYPE(_create)(uint32_t (*hash)(KEY_TYPE),
                      bool (*comp)(KEY_TYPE, KEY_TYPE)) {
    TS_TYPE table = {
        .capacity = HASHTABLE_DEFAULT_CAPACITY,
        .hash = hash,
        .comp = comp,
        .length = 0,
        .buckets = malloc(sizeof(LinkedList *) * HASHTABLE_DEFAULT_CAPACITY)};
    if (table.buckets == NULL) {
        PANIC("Memory allocation failed");
    }
    for (uint32_t i = 0; i < HASHTABLE_DEFAULT_CAPACITY; i++) {
        table.buckets[i] = linkedlist_create(NS_TYPE);
    }
    return table;
};

/// @brief Free the hashtable
/// @param table pointer to the hashtable
void TYPE(_free)(TS_TYPE *table) {
    for (uint32_t i = 0; i < table->capacity; i++) {
        linkedlist_free(table->buckets[i]);
    }
    free(table->buckets);
};

/// @brief Insert a key-value pair into the hashtable. Overwrites the value if
/// the key already exists
/// @param table pointer to the hashtable
/// @param key key to insert
/// @param value value to insert
void TYPE(_set)(TS_TYPE *table, KEY_TYPE key, VALUE_TYPE value) {
    uint32_t index = table->hash(key) % table->capacity;
    LinkedList *bucket = table->buckets[index];
    LinkedListIterator iterator = linkedlist_iterator(bucket);
    NS_TYPE *node;
    while ((node = linkedlist_iterator_next(&iterator)) != NULL) {
        if (table->comp(node->key, key)) {
            node->value = value;  // Overwrite the value
            return;
        }
    }
    NS_TYPE new_node = {
        .key = key,
        .value = value,
    };
    linkedlist_push(bucket, new_node);
    table->length++;

    // If length is above 75%, grow the table
    if (table->length > table->capacity * 0.75) {
        uint32_t old_capacity = table->capacity;
        table->capacity *= 2;
        LinkedList **old_buckets = table->buckets;
        table->buckets = malloc(sizeof(LinkedList *) * table->capacity);
        if (table->buckets == NULL) {
            PANIC("Memory allocation failed");
        }
        for (uint32_t i = 0; i < table->capacity; i++) {
            table->buckets[i] = linkedlist_create(NS_TYPE);
        }
        for (uint32_t i = 0; i < old_capacity; i++) {
            iterator = linkedlist_iterator(old_buckets[i]);
            while ((node = linkedlist_iterator_next(&iterator)) != NULL) {
                TYPE(_set)(table, node->key, node->value);
            }
            linkedlist_free(old_buckets[i]);
        }
        free(old_buckets);
    }
};

/// @brief Get a value from the hashtable
/// @param table pointer to the hashtable
/// @param key key to get the value
/// @return value of the key
VALUE_TYPE *TYPE(_get)(TS_TYPE *table, KEY_TYPE key) {
    uint32_t index = table->hash(key) % table->capacity;
    LinkedList *bucket = table->buckets[index];
    LinkedListIterator iterator = linkedlist_iterator(bucket);
    NS_TYPE *node;
    while ((node = linkedlist_iterator_next(&iterator)) != NULL) {
        if (table->comp(node->key, key)) {
            return &node->value;
        }
    }
    return NULL;
};

/// @brief Check if the hashtable contains a key
/// @param table pointer to the hashtable
/// @param key key to check
/// @return true if the key is in the hashtable, false otherwise
bool TYPE(_contains)(TS_TYPE *table, KEY_TYPE key) {
    uint32_t index = table->hash(key) % table->capacity;
    LinkedList *bucket = table->buckets[index];
    LinkedListIterator iterator = linkedlist_iterator(bucket);
    NS_TYPE *node;
    while ((node = linkedlist_iterator_next(&iterator)) != NULL) {
        if (table->comp(node->key, key)) {
            return true;
        }
    }
    return false;
};

/// @brief Delete a key from the hashtable
/// @param table pointer to the hashtable
/// @param key key to delete
void TYPE(_delete)(TS_TYPE *table, KEY_TYPE key) {
    uint32_t index = table->hash(key) % table->capacity;
    LinkedList *bucket = table->buckets[index];
    LinkedListIterator iterator = linkedlist_iterator(bucket);
    NS_TYPE *node;
    while ((node = linkedlist_iterator_next(&iterator)) != NULL) {
        if (table->comp(node->key, key)) {
            linkedlist_remove(bucket, *node);
            table->length--;
            return;
        }
    }
};

#ifndef HASHMAP_H
#define HASHMAP_H
// Predefined hash functions
// TODO better functions
uint32_t int_hash(int key) { return key; }
uint32_t cstr_hash(char *key) {
    size_t hash = 5381;
    size_t c;
    while ((c = (size_t)(*key++)))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}
#endif

#undef KEY_TYPE
#undef VALUE_TYPE
#undef HASHMAP_COMP
#endif
#endif