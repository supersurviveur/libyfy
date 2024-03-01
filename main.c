#include <stdio.h>

#include "src/libify.h"

CREATE_OPTION_TYPE(int)

Option(int) divide(int a, int b) {
    if (b == 0) {
        return None(int);
    }
    return Some(int, a / b);
}

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

    Option(int) r = divide(10, 1);
    int a = unwrap_option_or(r, 99);
    INFO("a: %d", a);
    
    return 0;
}