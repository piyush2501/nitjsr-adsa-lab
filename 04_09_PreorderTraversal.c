#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Stack structure
struct Stack {
    int top;
    int capacity;
    struct Node** array;
};

// Create stack
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct Node**)malloc(stack->capacity * sizeof(struct Node*));
    return stack;
}

// Check if stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Push onto stack
void push(struct Stack* stack, struct Node* node) {
    stack->array[++stack->top] = node;
}

// Pop from stack
struct Node* pop(struct Stack* stack) {
    return stack->array[stack->top--];
}

// Preorder Traversal without recursion
void preorderTraversal(struct Node* root) {
    if (root == NULL)
        return;

    // Create stack
    struct Stack* stack = createStack(100);

    // Push root
    push(stack, root);

    // Loop while stack is not empty
    while (!isEmpty(stack)) {
        // Pop node and print it\        struct Node* current = pop(stack);
        printf("%d ", current->data);

        // Push right first, so left is processed first
        if (current->right)
            push(stack, current->right);
        if (current->left)
            push(stack, current->left);
    }
}

// Driver code
int main() {
    // Constructing binary tree
    struct Node* root = newNode(18);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    printf("Preorder Traversal (Non-Recursive): ");
    preorderTraversal(root);

    return 0;
}
