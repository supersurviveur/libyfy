#include <stdio.h>

#include "libify.h"

int main() {
    int *array = array_create(int);
    array_push(array, 23000);
    array_push(array, 23010);
    array_push(array, 25);
    array_push(array, 34);
    print_int_array(array, false);
    array_free(array);

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