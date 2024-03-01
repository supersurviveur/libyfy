#include "str.h"

String *string_create() {
    String *string = (String *)malloc(sizeof(String));
    if (string == NULL) {
        PANIC("Memory allocation failed");
    }
    string->data =
        (char *)malloc(STRING_DEFAULT_CAPACITY * STRING_ELEMENT_SIZE);
    if (string->data == NULL) {
        PANIC("Memory allocation failed");
    }
    string->length = 0;
    string->capacity = STRING_DEFAULT_CAPACITY;
    return string;
}

String *string_from(char *cstr) {
    String *string = string_create();
    for (uint32_t i = 0; cstr[i] != '\0'; i++) {
        string_append(string, cstr[i]);
    }
    return string;
}

void string_free(String *string) {
    free(string->data);
    free(string);
}

char _string_get(int line, const char *file, String *string, uint32_t index) {
    if (index >= string->length) {
        PANIC_AT(line, file, "Index out of bounds");
    }
    return string->data[index];
}
void _string_set(int line, const char *file, String *string, uint32_t index,
                 char value) {
    if (index >= string->length) {
        PANIC_AT(line, file, "Index out of bounds");
    }
    string->data[index] = value;
}

void string_append(String *string, char value) {
    if (string->length >= string->capacity) {
        string->capacity *= 2;
        char *newData = (char *)realloc(string->data,
                                        string->capacity * STRING_ELEMENT_SIZE);
        if (newData == NULL) {
            PANIC("Memory allocation failed");
        }
        string->data = newData;
    }
    string->data[string->length] = value;
    string->length++;
}

void _string_push(String *string, String *other) {
    for (uint32_t i = 0; i < other->length; i++) {
        string_append(string, other->data[i]);
    }
}

void _string_push_cstr(String *string, char *other) {
    for (uint32_t i = 0; other[i] != '\0'; i++) {
        string_append(string, other[i]);
    }
}

String *string_concat(String *string, String *other) {
    String *newString = string_create();
    _string_push(newString, string);
    _string_push(newString, other);
    return newString;
}

bool _string_compare(String *string, String *other) {
    if (string->length != other->length) {
        return false;
    }
    for (uint32_t i = 0; i < string->length; i++) {
        if (string->data[i] != other->data[i]) {
            return false;
        }
    }
    return true;
}
bool _string_compare_cstr(String *string, char *other) {
    uint32_t i = 0;
    for (; i < string->length && other[i] != '\0'; i++) {
        if (string->data[i] != other[i]) {
            return false;
        }
    }
    return string->length == i && other[i] == '\0';
}

bool string_contains(String *string, char value) {
    for (uint32_t i = 0; i < string->length; i++) {
        if (string->data[i] == value) {
            return true;
        }
    }
    return false;
}