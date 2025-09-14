#include <stdio.h>
#include <stdlib.h>

#define M 3  // Order of B+ tree (max keys = M-1)

typedef struct BPTreeNode {
    int keys[M];
    struct BPTreeNode *children[M+1];
    int n;
    int leaf;
    struct BPTreeNode *next; // For leaf node linkage
} BPTreeNode;

BPTreeNode* createNode(int leaf) {
    BPTreeNode* node = (BPTreeNode*)malloc(sizeof(BPTreeNode));
    node->n = 0;
    node->leaf = leaf;
    node->next = NULL;
    for (int i=0; i<=M; i++) node->children[i] = NULL;
    return node;
}

void traverseLeaves(BPTreeNode* root) {
    while (!root->leaf) root = root->children[0];
    while (root) {
        for (int i=0; i<root->n; i++) printf("%d ", root->keys[i]);
        root = root->next;
    }
}

BPTreeNode* splitLeaf(BPTreeNode* parent, int i, BPTreeNode* leaf) {
    int mid = (M+1)/2;
    BPTreeNode* newLeaf = createNode(1);
    newLeaf->n = leaf->n - mid;
    for (int j=0; j<newLeaf->n; j++) newLeaf->keys[j] = leaf->keys[mid+j];
    leaf->n = mid;
    newLeaf->next = leaf->next;
    leaf->next = newLeaf;

    for (int j=parent->n; j>i; j--) {
        parent->children[j+1] = parent->children[j];
        parent->keys[j] = parent->keys[j-1];
    }
    parent->children[i+1] = newLeaf;
    parent->keys[i] = newLeaf->keys[0];
    parent->n++;
    return parent;
}

void insertNonFull(BPTreeNode* node, int k) {
    if (node->leaf) {
        int i=node->n-1;
        while (i>=0 && k<node->keys[i]) {
            node->keys[i+1]=node->keys[i];
            i--;
        }
        node->keys[i+1]=k;
        node->n++;
    } else {
        int i=node->n-1;
        while (i>=0 && k<node->keys[i]) i--;
        i++;
        if (node->children[i]->n == M) {
            node = splitLeaf(node,i,node->children[i]);
            if (k > node->keys[i]) i++;
        }
        insertNonFull(node->children[i], k);
    }
}

BPTreeNode* insert(BPTreeNode* root, int k) {
    if (root->n == M) {
        BPTreeNode* newRoot=createNode(0);
        newRoot->children[0]=root;
        newRoot = splitLeaf(newRoot,0,root);
        int i=0;
        if (k>newRoot->keys[0]) i++;
        insertNonFull(newRoot->children[i],k);
        return newRoot;
    } else {
        insertNonFull(root,k);
        return root;
    }
}

// ------------------ TEST ------------------
int main() {
    BPTreeNode* root = createNode(1);

    int arr[]={10,20,5,6,12,30,7,17};
    for (int i=0;i<8;i++) root = insert(root,arr[i]);

    printf("B+ Tree leaf traversal:\n");
    traverseLeaves(root);
    printf("\n");
    return 0;
}
