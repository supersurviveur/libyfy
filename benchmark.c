#include <memory.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "src/libify.h"

int test1(int a) {
    if (a % 2 == 0) {
        return 0;
    }
    return 1;
}

CREATE_RESULT_TYPE(int)

Result(int) test2(int a) {
    if (a % 2 == 0) {
        return Err(int, exception(ZeroDivideException, "Division by zero"));
    }
    return Ok(int, a / 2);
}

typedef struct Test {
    int a;
    int b;
} Test;

CREATE_RESULT_TYPE(Test);

Test test3(int a) {
    return (struct Test){.a = a, .b = 20};
}

Result(Test) test4(int a) {
    return Ok(Test, ((struct Test){.a = a, .b = 20}));
}


int random_int() {
    return rand() % 100;
}

int main() {
    uint64_t count = 100000000;
    TIME_START(1);
    for (uint64_t i = 0; i < count; i++) {
        test1(random_int());
    }
    TIME_END_S(1);

    TIME_START(2);
    for (uint64_t i = 0; i < count; i++) {
        test2(random_int());
    }
    TIME_END_S(2);

    TIME_START(3);
    for (uint64_t i = 0; i < count; i++) {
        test3(random_int());
    }
    TIME_END_S(3);
    
    TIME_START(4);
    for (uint64_t i = 0; i < count; i++) {
        test4(random_int());
    }
    TIME_END_S(4);
}