#include <stdio.h>
#include <stdlib.h>

#define T 3   // Minimum degree (t). B-Tree of order 2T-1

typedef struct BTreeNode {
    int keys[2*T-1];
    struct BTreeNode *children[2*T];
    int n;
    int leaf;
} BTreeNode;

BTreeNode* createNode(int leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->n = 0;
    node->leaf = leaf;
    for (int i=0; i<2*T; i++) node->children[i] = NULL;
    return node;
}

void traverse(BTreeNode* root) {
    int i;
    for (i=0; i<root->n; i++) {
        if (!root->leaf) traverse(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf) traverse(root->children[i]);
}

BTreeNode* splitChild(BTreeNode* parent, int i, BTreeNode* y) {
    BTreeNode* z = createNode(y->leaf);
    z->n = T-1;
    for (int j=0; j<T-1; j++) z->keys[j] = y->keys[j+T];
    if (!y->leaf) {
        for (int j=0; j<T; j++) z->children[j] = y->children[j+T];
    }
    y->n = T-1;
    for (int j=parent->n; j>=i+1; j--) parent->children[j+1] = parent->children[j];
    parent->children[i+1] = z;
    for (int j=parent->n-1; j>=i; j--) parent->keys[j+1] = parent->keys[j];
    parent->keys[i] = y->keys[T-1];
    parent->n++;
    return parent;
}

void insertNonFull(BTreeNode* node, int k) {
    int i = node->n - 1;
    if (node->leaf) {
        while (i>=0 && k < node->keys[i]) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = k;
        node->n++;
    } else {
        while (i>=0 && k < node->keys[i]) i--;
        i++;
        if (node->children[i]->n == 2*T-1) {
            splitChild(node, i, node->children[i]);
            if (k > node->keys[i]) i++;
        }
        insertNonFull(node->children[i], k);
    }
}

BTreeNode* insert(BTreeNode* root, int k) {
    if (root->n == 2*T-1) {
        BTreeNode* s = createNode(0);
        s->children[0] = root;
        s = splitChild(s, 0, root);
        int i = 0;
        if (k > s->keys[0]) i++;
        insertNonFull(s->children[i], k);
        return s;
    } else {
        insertNonFull(root, k);
        return root;
    }
}

// ------------------ TEST ------------------
int main() {
    BTreeNode* root = createNode(1);

    int arr[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int i=0; i<8; i++) root = insert(root, arr[i]);

    printf("B-Tree traversal:\n");
    traverse(root);
    printf("\n");
    return 0;
}
