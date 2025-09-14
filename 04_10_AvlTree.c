#include <stdio.h>
#include <stdlib.h>

// Structure for an AVL tree node
struct Node {
    int key;
    struct Node *left, *right;
    int height;
};

// Utility function to get height of node
int height(struct Node *n) {
    if (n == NULL) return 0;
    return n->height;
}
int max(int a, int b) {
    return (a > b) ? a : b;
}