#include <stdio.h>
#include <stdlib.h>

// Insertion Sort (used to sort each bucket)
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Bucket Sort function
void bucketSort(int arr[], int n) {
    // Find maximum value to know number of buckets
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }

    // Number of buckets = maxVal/10 + 1 (adjustable bucket size)
    int bucketCount = maxVal / 10 + 1;

    // Allocate memory for buckets
    int **buckets = (int **)malloc(bucketCount * sizeof(int *));
    int *bucketSizes = (int *)malloc(bucketCount * sizeof(int));
    int *bucketCap = (int *)malloc(bucketCount * sizeof(int));

    for (int i = 0; i < bucketCount; i++) {
        bucketSizes[i] = 0;
        bucketCap[i] = 5;  // initial capacity
        buckets[i] = (int *)malloc(bucketCap[i] * sizeof(int));
    }

    // Distribute array elements into buckets
    for (int i = 0; i < n; i++) {
        int idx = arr[i] / 10;  // bucket index (adjust divisor as needed)

        if (bucketSizes[idx] == bucketCap[idx]) {
            bucketCap[idx] *= 2;
            buckets[idx] = (int *)realloc(buckets[idx], bucketCap[idx] * sizeof(int));
        }
        buckets[idx][bucketSizes[idx]++] = arr[i];
    }

    // Sort individual buckets
    for (int i = 0; i < bucketCount; i++) {
        insertionSort(buckets[i], bucketSizes[i]);
    }

    // Concatenate all buckets into arr[]
    int k = 0;
    for (int i = 0; i < bucketCount; i++) {
        for (int j = 0; j < bucketSizes[i]; j++) {
            arr[k++] = buckets[i][j];
        }
    }

    // Free memory
    for (int i = 0; i < bucketCount; i++) {
        free(buckets[i]);
    }
    free(buckets);
    free(bucketSizes);
    free(bucketCap);
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

    bucketSort(arr, n);

    printf("Sorted array (Bucket Sort): ");
    printArray(arr, n);

    return 0;
}
