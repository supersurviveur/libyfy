#include "../src/linkedlist.h"
#include "../src/exception.h"

void tests_linkedlist() {
    LinkedList *list = linkedlist_create(int);
    linkedlist_push(list, 1);
    linkedlist_push(list, 2);
    linkedlist_push(list, 3);
    ASSERT(list->length == 3);
    ASSERT(linkedlist_first(list, int) == 1);
    ASSERT(linkedlist_last(list, int) == 3);

    ASSERT(linkedlist_contains(list, 1));
    ASSERT(linkedlist_contains(list, 2));
    ASSERT(linkedlist_contains(list, 3));
    ASSERT(!linkedlist_contains(list, 4));
    ASSERT(linkedlist_get(list, 1, int) == 2);

    ASSERT(linkedlist_index_of(list, 1) == 0);
    ASSERT(linkedlist_index_of(list, 2) == 1);
    ASSERT(linkedlist_index_of(list, 3) == 2);
    ASSERT(linkedlist_index_of(list, 4) == -1);

    int data;
    linkedlist_pop(list, &data);
    ASSERT(data == 3);
    linkedlist_shift(list, &data);
    ASSERT(data == 1);
    ASSERT(list->length == 1);



    linkedlist_free(list);
}