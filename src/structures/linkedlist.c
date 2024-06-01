#include "linkedlist.h"

Node *_linkedlist_create_node(LinkedList *list, void *data) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        PANIC("Memory allocation failed");
    }
    node->data = malloc(list->type_size);
    if (node->data == NULL) {
        PANIC("Memory allocation failed");
    }
    memcpy(node->data, data, list->type_size);
    node->next = NULL;
    return node;
}

void _linkedlist_free_node(Node *node) {
    free(node->data);
    free(node);
}

LinkedList *_linkedlist_create(uint32_t type_size) {
    LinkedList *list = malloc(sizeof(LinkedList));
    if (list == NULL) {
        PANIC("Memory allocation failed");
    }
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->type_size = type_size;
    return list;
}

void linkedlist_free(LinkedList *list) {
    Node *node = list->head;
    while (node != NULL) {
        Node *next = node->next;
        _linkedlist_free_node(node);
        node = next;
    }
    free(list);
}

void _linkedlist_push(LinkedList *list, void *data) {
    Node *node = _linkedlist_create_node(list, data);
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->length++;
}

void _linkedlist_unshift(LinkedList *list, void *data) {
    Node *node = _linkedlist_create_node(list, data);
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->head;
        list->head = node;
    }
    list->length++;
}

void linkedlist_pop(LinkedList *list, void *data) {
    if (list->length == 0) {
        PANIC("Cannot pop from an empty linked list");
    }
    Node *node = list->head;
    if (list->length == 1) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        while (node->next != list->tail) {
            node = node->next;
        }
        list->tail = node;
        node = node->next;
        list->tail->next = NULL;
    }
    memcpy(data, node->data, list->type_size);
    _linkedlist_free_node(node);
    list->length--;
}

void linkedlist_shift(LinkedList *list, void *data) {
    if (list->length == 0) {
        PANIC("Cannot shift from an empty linked list");
    }
    Node *node = list->head;
    list->head = list->head->next;
    memcpy(data, node->data, list->type_size);
    _linkedlist_free_node(node);
    list->length--;
}

void *_linkedlist_first(LinkedList *list) {
    if (list->length == 0) {
        PANIC("Cannot get the first element from an empty linked list");
    }
    return list->head->data;
}

void *_linkedlist_last(LinkedList *list) {
    if (list->length == 0) {
        PANIC("Cannot get the last element from an empty linked list");
    }
    return list->tail->data;
}

bool _linkedlist_contains(LinkedList *list, void *data) {
    Node *node = list->head;
    while (node != NULL) {
        if (memcmp(node->data, data, list->type_size) == 0) {
            return true;
        }
        node = node->next;
    }
    return false;
}

void *_linkedlist_get(LinkedList *list, uint32_t index) {
    if (index >= list->length) {
        PANIC("Index out of range");
    }
    Node *node = list->head;
    for (uint32_t i = 0; i < index; i++) {
        node = node->next;
    }
    return node->data;
}

int32_t _linkedlist_index_of(LinkedList *list, void *data) {
    Node *node = list->head;
    for (uint32_t i = 0; i < list->length; i++) {
        if (memcmp(node->data, data, list->type_size) == 0) {
            return i;
        }
        node = node->next;
    }
    return -1;
}

void _linkedlist_remove(LinkedList *list, void *data) {
    Node *node = list->head;
    Node *prev = NULL;
    while (node != NULL) {
        if (memcmp(node->data, data, list->type_size) == 0) {
            if (prev == NULL) {
                list->head = node->next;
            } else {
                prev->next = node->next;
            }
            if (node == list->tail) {
                list->tail = prev;
            }
            _linkedlist_free_node(node);
            list->length--;
            return;
        }
        prev = node;
        node = node->next;
    }
}

LinkedListIterator linkedlist_iterator(LinkedList *list) {
    LinkedListIterator iterator = {
        .list = list,
        .node = list->head,
    };
    return iterator;
}

void *linkedlist_iterator_next(LinkedListIterator *iterator) {
    if (iterator->node == NULL) {
        return NULL;
    }
    void *data = iterator->node->data;
    iterator->node = iterator->node->next;
    return data;
}