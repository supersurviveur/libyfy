#include "tests.h"

#include "libyfy.h"

int main() {
    tests_vector();
    tests_hashtable();
    tests_linkedlist();
    tests_heap();
    tests_binarytree();

    INFO("All tests passed");
    return 0;
}