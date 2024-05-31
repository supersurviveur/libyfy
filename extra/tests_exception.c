#include "../src/exception.h"
#include <string.h>

CREATE_EXCEPTION(ZeroDivideException);

CREATE_RESULT_TYPE(int)

Result(int) divide(int a, int b) {
    if (b == 0) {
        return Err(int, exception(ZeroDivideException, "Division by zero"));
    }
    return Ok(int, a / b);
}

typedef struct {
    int a;
    int b;
} TestResult;
CREATE_RESULT_TYPE(TestResult)

Result(TestResult) divideResult(int a, int b) {
    if (b == 0) {
        return Err(TestResult, exception(ZeroDivideException, "Division by zero"));
    }
    TestResult t = {a, b};
    return Ok(TestResult, t);
}

void tests_exception() {
    Result(int) r = divide(10, 0);
    ASSERT(is_err(r));
    ASSERT(is_exception(r, ZeroDivideException));
    ASSERT(strcmp(r.error.message, "Division by zero") == 0);
    ASSERT(unwrap_or(r, 99) == 99);
    r = divide(10, 2);
    ASSERT(is_ok(r));
    ASSERT(unwrap(r) == 5);
    ASSERT(unwrap_or(r, 99) == 5);

    Result(TestResult) t = divideResult(10, 0);
    ASSERT(is_err(t));
    ASSERT(is_exception(t, ZeroDivideException));
    ASSERT(strcmp(t.error.message, "Division by zero") == 0);
    ASSERT(unwrap_or(t, ((TestResult){99, 99})).a == 99);
    ASSERT(unwrap_or(t, ((TestResult){99, 99})).b == 99);
    t = divideResult(10, 2);
    ASSERT(is_ok(t));
    ASSERT(unwrap(t).a == 10);
    ASSERT(unwrap(t).b == 2);
    ASSERT(unwrap_or(t, ((TestResult){99, 99})).a == 10);
    ASSERT(unwrap_or(t, ((TestResult){99, 99})).b == 2);
}