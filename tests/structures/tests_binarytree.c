#include "libyfy.h"

void print_char(void *value) {
    printf("%c%c", *(char *)value, *(char *)value);
}

void tests_binarytree() {
    BinaryTree tree = binarytree_create(char);
    tree.root = tree_node_create('a');
    tree.root->left = tree_node_create('b');
    tree.root->right = tree_node_create('c');
    tree.root->left->left = tree_node_create('d');
    tree.root->left->right = tree_node_create('e');
    tree.root->right->left = tree_node_create('f');
    tree.root->right->right = tree_node_create('g');
    tree.root->right->right->left = tree_node_create('h');
    tree.root->left->left->right = tree_node_create('d');

    ASSERT(binarytree_height(&tree) == 3);
    // print_binarytree(&tree, print_char, 2);

    binarytree_free(&tree);
}