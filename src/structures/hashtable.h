#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../exception.h"
#include "linkedlist.h"

#define HASHTABLE_DEFAULT_CAPACITY 128

typedef struct {
    void *key;
    void *value;
} HashNode;

// Hashtable using linked list
typedef struct {
    uint32_t key_size;
    uint32_t type_size;
    uint32_t length;
    uint32_t capacity;
    uint32_t (*hash)(const void *);
    LinkedList **buckets;
} HashTable;

HashTable *_hashtable_create(uint32_t key_size, uint32_t type_size,
                             uint32_t (*hash)(const void *));
void _hashtable_set(HashTable *table, void *key, void *value);
void *_hashtable_get(HashTable *table, void *key);
bool _hashtable_contains(HashTable *table, void *key);
void _hashtable_delete(HashTable *table, void *key);

/// @brief Create an empty hashtable
/// @param key_type type of the key
/// @param value_type type of the value
/// @param hash hash function for the key
#define hashtable_create(key_type, value_type, hash) \
    _hashtable_create(sizeof(key_type), sizeof(value_type), hash)

/// @brief Free the hashtable
/// @param table pointer to the hashtable
void hashtable_free(HashTable *table);

/// @brief Insert a key-value pair into the hashtable. Overwrites the value if
/// the key already exists
/// @param table pointer to the hashtable
/// @param key key to insert
/// @param value value to insert
#define hashtable_set(table, key, value)       \
    {                                          \
        typeof(key) _key = key;                \
        typeof(value) _value = value;          \
        _hashtable_set(table, &_key, &_value); \
    }

/// @brief Get a value from the hashtable
/// @param table pointer to the hashtable
/// @param key key to get the value
/// @return value of the key
#define hashtable_get(table, key, value_type)        \
    ({                                               \
        typeof(key) _key = key;                      \
        *(value_type *)_hashtable_get(table, &_key); \
    })

/// @brief Check if the hashtable contains a key
/// @param table pointer to the hashtable
/// @param key key to check
/// @return true if the key is in the hashtable, false otherwise
#define hashtable_contains(table, key)     \
    ({                                     \
        typeof(key) _key = key;            \
        _hashtable_contains(table, &_key); \
    })


/// @brief Delete a key from the hashtable
/// @param table pointer to the hashtable
/// @param key key to delete
#define hashtable_delete(table, key)     \
    {                                    \
        typeof(key) _key = key;          \
        _hashtable_delete(table, &_key); \
    }


// Predefined hash functions
uint32_t int_hash(const void *key);
uint32_t cstr_hash(const void *key);

#endif  // HASHTABLE_H