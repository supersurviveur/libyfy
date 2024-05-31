#include "../src/exception.h"
#include "../src/option.h"

CREATE_OPTION_TYPE(int)

Option(int) divide2(int a, int b) {
    if (b == 0) {
        return None(int);
    }
    return Some(int, a / b);
}

typedef struct {
    int a;
    int b;
} TestOption;
CREATE_OPTION_TYPE(TestOption)

Option(TestOption) divideOption(int a, int b) {
    if (b == 0) {
        return None(TestOption);
    }
    TestOption t = {a, b};
    return Some(TestOption, t);
}

void tests_option() {
    Option(int) r = divide2(10, 0);
    ASSERT(is_none(r));
    ASSERT(unwrap_option_or(r, 99) == 99);
    r = divide2(10, 2);
    ASSERT(is_some(r));
    ASSERT(unwrap_option(r) == 5);
    ASSERT(unwrap_option_or(r, 99) == 5);

    Option(TestOption) t = divideOption(10, 0);
    ASSERT(is_none(t));
    ASSERT(unwrap_option_or(t, ((TestOption){99, 99})).a == 99);
    ASSERT(unwrap_option_or(t, ((TestOption){99, 99})).b == 99);
    t = divideOption(10, 2);
    ASSERT(is_some(t));
    ASSERT(unwrap_option(t).a == 10);
    ASSERT(unwrap_option(t).b == 2);
    ASSERT(unwrap_option_or(t, ((TestOption){99, 99})).a == 10);
    ASSERT(unwrap_option_or(t, ((TestOption){99, 99})).b == 2);
}