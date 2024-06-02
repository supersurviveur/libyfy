#pragma once

#include <malloc.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../exception.h"

typedef struct TreeNode {
    void *value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct BinaryTree {
    TreeNode *root;
    size_t stride;
} BinaryTree;

// private functions
TreeNode *_tree_node_create(size_t stride, void *value);
void tree_node_free(TreeNode *node);
BinaryTree _binarytree_create(size_t stride);
void binarytree_free(BinaryTree *tree);

#define binarytree_create(type) _binarytree_create(sizeof(type))
#define tree_node_create(value)                         \
    ({                                                  \
        typeof(value) tmp = value;                      \
        _tree_node_create(sizeof(typeof(value)), &tmp); \
    })

#define binarytree_set_root(tree, value)  \
    ({                                    \
        typeof(value) tmp = value;        \
        _binarytree_set_root(tree, &tmp); \
    })

size_t binarytree_height(BinaryTree *tree);

/// @brief Print a binary tree
/// @param tree The tree to print
/// @param print The function to print the value of each node (center the value for better visualization, print `width` characters each time)
/// @param width The maximum width of the printing (max is 20)
void print_binarytree(BinaryTree *tree, void (*print)(void *), uint8_t width);