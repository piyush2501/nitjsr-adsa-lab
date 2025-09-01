#include <stdio.h>

// Function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Recursive Radix Exchange Sort
void radixExchangeSort(int arr[], int left, int right, int bit) {
    if (left >= right || bit < 0)
        return;

    int i = left;
    int j = right;

    // Partition elements based on current bit
    while (i <= j) {
        while (i <= j && ((arr[i] >> bit) & 1) == 0) i++;  // bit = 0 on left
        while (i <= j && ((arr[j] >> bit) & 1) == 1) j--;  // bit = 1 on right
        if (i < j) {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }

    // Recursively sort left and right partitions
    radixExchangeSort(arr, left, j, bit - 1);
    radixExchangeSort(arr, i, right, bit - 1);
}

// Utility function to find maximum bit position
int getMaxBit(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    int bit = 0;
    while (max > 0) {
        max >>= 1;
        bit++;
    }
    return bit - 1;  // most significant bit index
}

// Function to print an array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Driver Program
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

    int maxBit = getMaxBit(arr, n);
    radixExchangeSort(arr, 0, n - 1, maxBit);

    printf("Sorted array (Radix Exchange Sort): ");
    printArray(arr, n);

    return 0;
}
