#include "hashtable.h"

HashTable *_hashtable_create(uint32_t key_size, uint32_t type_size,
                             uint32_t (*hash)(const void *)) {
    HashTable *table = malloc(sizeof(HashTable));
    if (table == NULL) {
        PANIC("Memory allocation failed");
    }
    table->key_size = key_size;
    table->type_size = type_size;
    table->hash = hash;
    table->buckets = malloc(sizeof(LinkedList) * HASHTABLE_DEFAULT_CAPACITY);
    if (table->buckets == NULL) {
        PANIC("Memory allocation failed");
    }
    for (uint32_t i = 0; i < HASHTABLE_DEFAULT_CAPACITY; i++) {
        table->buckets[i] = linkedlist_create(HashNode);
    }
    table->length = 0;
    table->capacity = HASHTABLE_DEFAULT_CAPACITY;
    return table;
}

void hashtable_free(HashTable *table) {
    for (uint32_t i = 0; i < table->capacity; i++) {
        LinkedListIterator iterator = linkedlist_iterator(table->buckets[i]);
        HashNode *node;
        while ((node = linkedlist_iterator_next(&iterator)) != NULL) {
            free(node->key);
            free(node->value);
        }
        linkedlist_free(table->buckets[i]);
    }
    free(table->buckets);
    free(table);
}

void _hashtable_set(HashTable *table, void *key, void *value) {
    uint32_t index = table->hash(key) % table->capacity;
    LinkedList *bucket = table->buckets[index];
    LinkedListIterator iterator = linkedlist_iterator(bucket);
    HashNode *node;
    while ((node = linkedlist_iterator_next(&iterator)) != NULL) {
        if (memcmp(node->key, key, table->key_size) == 0) {
            memcpy(node->value, value,
                   table->type_size);  // Overwrite the value
            return;
        }
    }
    HashNode new_node = {
        .key = malloc(table->key_size),
        .value = malloc(table->type_size),
    };
    linkedlist_push(bucket, new_node);
    memcpy(new_node.key, key, table->key_size);
    memcpy(new_node.value, value, table->type_size);
    table->length++;
}
void *_hashtable_get(HashTable *table, void *key) {
    uint32_t index = table->hash(key) % table->capacity;
    LinkedList *bucket = table->buckets[index];
    LinkedListIterator iterator = linkedlist_iterator(bucket);
    HashNode *node;
    while ((node = linkedlist_iterator_next(&iterator)) != NULL) {
        if (memcmp(node->key, key, table->key_size) == 0) {
            return node->value;
        }
    }
    return NULL;
}

bool _hashtable_contains(HashTable *table, void *key) {
    uint32_t index = table->hash(key) % table->capacity;
    LinkedList *bucket = table->buckets[index];
    LinkedListIterator iterator = linkedlist_iterator(bucket);
    HashNode *node;
    while ((node = linkedlist_iterator_next(&iterator)) != NULL) {
        if (memcmp(node->key, key, table->key_size) == 0) {
            return true;
        }
    }
    return false;
}

void _hashtable_delete(HashTable *table, void *key) {
    uint32_t index = table->hash(key) % table->capacity;
    LinkedList *bucket = table->buckets[index];
    LinkedListIterator iterator = linkedlist_iterator(bucket);
    HashNode *node;
    while ((node = linkedlist_iterator_next(&iterator)) != NULL) {
        if (memcmp(node->key, key, table->key_size) == 0) {
            free(node->key);
            free(node->value);
            linkedlist_remove(bucket, *node);
            table->length--;
            return;
        }
    }
}

// Hash functions
uint32_t int_hash(const void *key) { return *(int *)key; }
uint32_t cstr_hash(const void *key) {
    const char *str = *(const char **)key;

    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}