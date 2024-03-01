#include "../src/str.h"

void tests_string() {
    String *string = string_create();
    ASSERT(string->data != NULL);
    ASSERT(string->length == 0);
    ASSERT(string->capacity == STRING_DEFAULT_CAPACITY);

    string_append(string, 'a');
    ASSERT(string->length == 1);
    ASSERT(string->capacity == STRING_DEFAULT_CAPACITY);
    ASSERT(string_get(string, 0) == 'a');
    string_append(string, 'b');
    ASSERT(string->length == 2);
    ASSERT(string->capacity == STRING_DEFAULT_CAPACITY);
    ASSERT(string_get(string, 1) == 'b');
    string_append(string, 'c');
    ASSERT(string->length == 3);
    ASSERT(string->capacity == STRING_DEFAULT_CAPACITY * 2);
    ASSERT(string_get(string, 2) == 'c');

    string_push(string, "def");
    ASSERT(string->length == 6);
    ASSERT(string_get(string, 3) == 'd');
    ASSERT(string_get(string, 4) == 'e');
    ASSERT(string_get(string, 5) == 'f');

    String *other = string_create();
    string_push(other, string);
    ASSERT(other->length == 6);
    ASSERT(string_get(other, 0) == 'a');
    ASSERT(string_get(other, 5) == 'f');

    String *concat = string_concat(string, other);
    ASSERT(concat->length == 12);
    ASSERT(string_get(concat, 0) == 'a');
    ASSERT(string_get(concat, 5) == 'f');
    ASSERT(string_get(concat, 6) == 'a');
    ASSERT(string_get(concat, 11) == 'f');

    String *from = string_from("abc");
    ASSERT(from->length == 3);
    ASSERT(from->capacity == STRING_DEFAULT_CAPACITY * 2);
    ASSERT(string_get(from, 0) == 'a');
    ASSERT(string_get(from, 1) == 'b');
    ASSERT(string_get(from, 2) == 'c');

    ASSERT(!string_compare(from, string));
    ASSERT(string_compare(from, "abc"));
    ASSERT(!string_compare(from, "abcd"));
    ASSERT(string_compare(string, other));

    ASSERT(string_contains(concat, 'a'));
    ASSERT(!string_contains(concat, 'z'));

    string_free(from);
    string_free(concat);
    string_free(string);
    string_free(other);
}