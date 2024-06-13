#pragma once

#include <malloc.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../exception.h"

typedef struct BinaryTree {
    void *value;
    struct BinaryTree *left;
    struct BinaryTree *right;
} BinaryTree;

// private functions
BinaryTree *_binarytree_create(size_t stride, void *value);
void binarytree_free(BinaryTree *node);

#define binarytree_create(value)                         \
    ({                                                   \
        typeof(value) tmp = value;                       \
        _binarytree_create(sizeof(typeof(value)), &tmp); \
    })

int64_t binarytree_height(BinaryTree *tree);

/// @brief Print a binary tree
/// @param tree The tree to print
/// @param print The function to print the value of each node (center the value
/// for better visualization, print `width` characters each time)
/// @param width The maximum width of the printing (max is 20)
void print_binarytree(BinaryTree *tree, void (*print)(void *), uint8_t width);