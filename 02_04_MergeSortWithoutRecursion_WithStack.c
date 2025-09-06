#include <stdio.h>
#include <stdlib.h>

// Structure to represent a stack frame (a subarray range)
typedef struct {
    int left;
    int right;
    int state; // 0 = first time (divide), 1 = second time (merge)
} Frame;

// Merge function
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

// Iterative Merge Sort using stack
void mergeSort(int arr[], int n) {
    Frame *stack = (Frame *)malloc(n * sizeof(Frame) * 2);
    int top = -1;

    // push initial range
    stack[++top] = (Frame){0, n - 1, 0};

    while (top >= 0) {
        Frame curr = stack[top--];

        if (curr.left >= curr.right)
            continue;

        if (curr.state == 0) {
            int mid = (curr.left + curr.right) / 2;

            // Push current frame again with state=1 (for merging later)
            stack[++top] = (Frame){curr.left, curr.right, 1};

            // Push right subproblem
            stack[++top] = (Frame){mid + 1, curr.right, 0};

            // Push left subproblem
            stack[++top] = (Frame){curr.left, mid, 0};
        } else {
            int mid = (curr.left + curr.right) / 2;
            merge(arr, curr.left, mid, curr.right);
        }
    }
    free(stack);
}


int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    mergeSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
