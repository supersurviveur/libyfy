#include "libyfy.h"

void print_char(void *value) { printf("%c%c", *(char *)value, *(char *)value); }

void tests_binarytree() {
    BinaryTree *tree = binarytree_create('a');
    tree->left = binarytree_create('b');
    tree->right = binarytree_create('c');
    tree->left->left = binarytree_create('d');
    tree->left->right = binarytree_create('e');
    tree->right->left = binarytree_create('f');
    tree->right->right = binarytree_create('g');
    tree->right->right->left = binarytree_create('h');
    tree->left->left->right = binarytree_create('d');

    ASSERT(binarytree_height(tree) == 3);
    // print_binarytree(tree, print_char, 2);

    binarytree_free(tree);
}