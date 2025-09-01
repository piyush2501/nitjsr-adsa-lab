#include <stdio.h>
#include <stdlib.h>

void countingSort(int arr[], int n) {
    int i;
    
    // Find the maximum element in the array
    int max = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    // Create a count array and initialize to 0
    int *count = (int*)calloc(max + 1, sizeof(int));

    // Store the count of each element
    for (i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // Reconstruct the sorted array
    int index = 0;
    for (i = 0; i <= max; i++) {
        while (count[i] > 0) {
            arr[index++] = i;
            count[i]--;
        }
    }

    free(count);
}

int main() {
    int n, i;
    
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements: ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    countingSort(arr, n);

    printf("Sorted array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
