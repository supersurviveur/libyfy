#include <stdio.h>

#include "libyfy.h"

int main() {
    int *vector = vector_create(int);
    vector_push(vector, 23000);
    vector_push(vector, 23010);
    vector_push(vector, 25);
    vector_push(vector, 34);
    print_int_vector(vector, false);
    vector_free(vector);

    TIME_START(1);
    TRACE("Hello from main");
    DEBUG("This is a debug message");
    INFO("Hello from main");
    WARN("This is a warn");
    ERROR("This is an error");
    TIME_END(1);
    TIME_END_MS(1);
    TIME_END_S(1);
    // PANIC("This is a panic message"

    
    return 0;
}