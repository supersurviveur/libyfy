#include <stdio.h>

#include "libyfy.h"

int main() {

    TIME_START(1);
    TRACE("Hello from main");
    DEBUG("This is a debug message");
    INFO("Hello from main");
    WARN("This is a warn");
    ERROR("This is an error");
    TIME_END(1);
    TIME_END_MS(1);
    TIME_END_S(1);
    // PANIC("This is a panic message");

    
    return 0;
}