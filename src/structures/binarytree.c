#include "binarytree.h"

BinaryTree *_binarytree_create(size_t stride, void *value) {
    BinaryTree *node = malloc(sizeof(BinaryTree));
    if (node == NULL) {
        PANIC("Memory allocation failed");
    }
    node->value = malloc(stride);
    if (node->value == NULL) {
        PANIC("Memory allocation failed");
    }
    memcpy(node->value, value, stride);
    node->left = NULL;
    node->right = NULL;
    return node;
}

void binarytree_free(BinaryTree *node) {
    if (node->left != NULL) {
        binarytree_free(node->left);
    }
    if (node->right != NULL) {
        binarytree_free(node->right);
    }
    free(node->value);
    free(node);
}

int64_t binarytree_height(BinaryTree *tree) {
    if (tree == NULL) return -1;
    int a = binarytree_height(tree->left);
    int b = binarytree_height(tree->right);
    return 1 + (a > b ? a : b);
}

void print_binarytree_internal(void ***matrix, BinaryTree *tree, int col,
                               int row, int height) {
    if (tree == NULL) return;
    matrix[row][col] = tree->value;

    int offset = height >= 2 ? (1 << (height - 1)) : 1;
    print_binarytree_internal(matrix, tree->left, col - offset, row + 1,
                              height - 1);
    print_binarytree_internal(matrix, tree->right, col + offset, row + 1,
                              height - 1);
}

void print_binarytree(BinaryTree *tree, void (*print)(void *), uint8_t width) {
    if (width > 20 || width < 2) {
        PANIC("Width must be between 2 and 20");
    }
    // Multiply by 3 because the char takes 3 bytes
    char spaces[21] = "                    ";
    char lines[21 * 3] = "────────────────────";
    spaces[width - 1] = '\0';
    lines[(width - 1) * 3] = '\0';

    size_t height = binarytree_height(tree);
    size_t max_width = 1 << (height + 1);
    void ***matrix = malloc(sizeof(void **) * (height + 1));
    if (matrix == NULL) {
        ASSERT("Memory allocation failed")
    }
    for (size_t i = 0; i < (height + 1); i++) {
        matrix[i] = malloc(sizeof(void *) * max_width);
        if (matrix[i] == NULL) {
            ASSERT("Memory allocation failed")
        }
        for (size_t j = 0; j < max_width; j++) {
            matrix[i][j] = NULL;
        }
    }
    // Fill the matrix
    print_binarytree_internal(matrix, tree, max_width / 2, 0, height);

    for (size_t i = 0; i < height + 1; i++) {
        size_t current_width = (height - 1) < i ? 0 : 1 << (height - 1 - i);
        for (size_t j = 0; j < max_width; j++) {
            if (matrix[i][j] == NULL) {
                printf(" %s", spaces);
            } else {
                print(matrix[i][j]);
            }
        }
        printf("\n");

        bool link = false;
        for (size_t j = 0; j < max_width; j++) {
            if (i != height && matrix[i + 1][j] != NULL) {
                if (link) {
                    printf("┐%s", spaces);
                } else {
                    printf("┌%s", lines);
                }
                link = !link;
            } else if (matrix[i][j] != NULL) {
                if (link && j + current_width < max_width && i != height &&
                    matrix[i + 1][j + current_width] == NULL) {
                    link = false;
                    printf("┘%s", spaces);
                } else if (link) {
                    printf("┴%s", lines);
                } else if (j + current_width < max_width && i != height &&
                           matrix[i + 1][j + current_width] != NULL) {
                    printf("└%s", lines);
                    link = true;
                } else {
                    printf(" %s", spaces);
                }
            } else if (link) {
                printf("─%s", lines);
            } else {
                printf(" %s", spaces);
            }
        }
        printf("\n");
    }
    for (size_t i = 0; i < (height + 1); i++) {
        free(matrix[i]);
    }
    free(matrix);
}