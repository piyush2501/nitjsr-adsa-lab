#include <stdio.h>
#include <stdlib.h>

// Node for linked list (for handling collisions)
struct Node {
    int data;
    struct Node* next;
};

// Insert in sorted order into the linked list (to keep bucket sorted)
void insertSorted(struct Node** head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    // Empty list or new node should be at head
    if (*head == NULL || (*head)->data >= value) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    struct Node* current = *head;
    while (current->next != NULL && current->next->data < value)
        current = current->next;

    newNode->next = current->next;
    current->next = newNode;
}

// Address Calculation Sort
void addressCalculationSort(int arr[], int n) {
    // Find max value to define number of buckets
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    int bucketCount = n; // often use n buckets (can vary)

    // Array of bucket heads
    struct Node** buckets = (struct Node**)malloc(bucketCount * sizeof(struct Node*));
    for (int i = 0; i < bucketCount; i++)
        buckets[i] = NULL;

    // Hash function: f(x) = (x * n) / (max+1)
    for (int i = 0; i < n; i++) {
        int idx = (arr[i] * n) / (max + 1);
        insertSorted(&buckets[idx], arr[i]);
    }

    // Collect elements back into arr[]
    int k = 0;
    for (int i = 0; i < bucketCount; i++) {
        struct Node* temp = buckets[i];
        while (temp != NULL) {
            arr[k++] = temp->data;
            temp = temp->next;
        }
    }

    // Free memory
    for (int i = 0; i < bucketCount; i++) {
        struct Node* temp = buckets[i];
        while (temp != NULL) {
            struct Node* del = temp;
            temp = temp->next;
            free(del);
        }
    }
    free(buckets);
}

// Function to print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Driver code
int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Original array: ");
    printArray(arr, n);

    addressCalculationSort(arr, n);

    printf("Sorted array (Address Calculation Sort): ");
    printArray(arr, n);

    return 0;
}
