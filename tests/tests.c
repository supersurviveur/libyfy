#include "tests.h"

#include "../src/logging.h"

int main() {
    tests_array();
    tests_exception();
    tests_option();
    tests_string();
    tests_hashtable();
    tests_linkedlist();

    INFO("All tests passed");
    return 0;
}