#include "tests.h"

#include "libyfy.h"

int main() {
    tests_vector();
    tests_hashtable();
    tests_linkedlist();

    INFO("All tests passed");
    return 0;
}