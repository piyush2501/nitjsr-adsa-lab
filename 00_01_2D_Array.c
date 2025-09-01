#include <stdio.h>

int main() {
    int rows, cols;

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter number of columns: ");
    scanf("%d", &cols);

    int arr[rows][cols];   // VLA (variable length array in C99+)

    // Initialize all elements with 0
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = 0;
        }
    }

    printf("Enter elements (row by row). Enter -1 to skip:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int temp;
            scanf("%d", &temp);
            if (temp != -1) {   // if user enters -1, keep as 0
                arr[i][j] = temp;
            }
        }
    }

    // Print final array
    printf("Final 2D array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}

