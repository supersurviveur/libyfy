#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../exception.h"

typedef struct _Node {
    void *data;
    struct _Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    uint32_t length;
    uint32_t type_size;
} LinkedList;

// Private functions
Node *_linkedlist_create_node(LinkedList *list, void *data);
void _linkedlist_free_node(Node *node);
LinkedList *_linkedlist_create(uint32_t type_size);
void _linkedlist_push(LinkedList *list, void *data);
void _linkedlist_unshift(LinkedList *list, void *data);
void *_linkedlist_first(LinkedList *list);
void *_linkedlist_last(LinkedList *list);
void *_linkedlist_get(LinkedList *list, uint32_t index);
bool _linkedlist_contains(LinkedList *list, void *data);
int32_t _linkedlist_index_of(LinkedList *list, void *data);
void _linkedlist_remove(LinkedList *list, void *data);

// Public functions
/// @brief Create an empty linked list
/// @param type type of the data
/// @return pointer to the linked list
#define linkedlist_create(type) _linkedlist_create(sizeof(type))

/// @brief Free the linked list
/// @param list pointer to the linked list
void linkedlist_free(LinkedList *list);

/// @brief Insert data at the end of the linked list
/// @param list pointer to the linked list
/// @param data data to insert
#define linkedlist_push(list, data)     \
    {                                   \
        typeof(data) _data = data;      \
        _linkedlist_push(list, &_data); \
    }

/// @brief Insert data at the beginning of the linked list
/// @param list pointer to the linked list
/// @param data data to insert
#define linkedlist_unshift(list, data)     \
    {                                      \
        typeof(data) _data = data;         \
        _linkedlist_unshift(list, &_data); \
    }

/// @brief Remove the last element from the linked list
/// @param list pointer to the linked list
/// @param data pointer to store the removed data
void linkedlist_pop(LinkedList *list, void *data);

/// @brief Remove the first element from the linked list
/// @param list pointer to the linked list
/// @param data pointer to store the removed data
void linkedlist_shift(LinkedList *list, void *data);

/// @brief Get the first element from the linked list
/// @param list pointer to the linked list
#define linkedlist_first(list, value_type) \
    *(value_type *)_linkedlist_first(list)

/// @brief Get the last element from the linked list
/// @param list pointer to the linked list
#define linkedlist_last(list, value_type) *(value_type *)_linkedlist_last(list)

/// @brief Check if the linked list is empty
/// @param list pointer to the linked list
/// @return true if the linked list is empty, false otherwise
#define linkedlist_is_empty(list) ((list)->length == 0)

/// @brief Check if the linked list contains the data
/// @param list pointer to the linked list
/// @param data data to check
/// @return true if the linked list contains the data, false otherwise
#define linkedlist_contains(list, data)     \
    ({                                      \
        typeof(data) _data = data;          \
        _linkedlist_contains(list, &_data); \
    })

/// @brief Get the data at the index
/// @param list pointer to the linked list
/// @param index index of the data
/// @param type type of the data
/// @return data at the index
#define linkedlist_get(list, index, value_type) \
    *(value_type *)_linkedlist_get(list, index)

/// @brief Get the index of the data
/// @param list pointer to the linked list
/// @param data data to get the index
/// @return index of the data, -1 if not found
#define linkedlist_index_of(list, data)     \
    ({                                      \
        typeof(data) _data = data;          \
        _linkedlist_index_of(list, &_data); \
    })

/// @brief Remove the data from the linked list
/// @param list pointer to the linked list
/// @param data data to remove
#define linkedlist_remove(list, data)     \
    {                                     \
        typeof(data) _data = data;        \
        _linkedlist_remove(list, &_data); \
    }

typedef struct {
    LinkedList *list;
    Node *node;
} LinkedListIterator;

/// @brief Iterate through the linked list
/// @param list pointer to the linked list
/// @return iterator for the linked list
LinkedListIterator linkedlist_iterator(LinkedList *list);

/// @brief Get the next element from the iterator
/// @param iterator pointer to the iterator
/// @return pointer to the next element
void *linkedlist_iterator_next(LinkedListIterator *iterator);

#endif  // LINKEDLIST_H
