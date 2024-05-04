#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));


    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for large l and r
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

int main() {
    srand(time(NULL));

    int n = 1 << 20;  // n=2^20

    int *arr = (int *)malloc(n * sizeof(int));//int arr[n]

    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }

    for (int k = 0; k <= 20; k++) {
        // Randomly swap array elements k times
        int swaps = 1 << k;
        for (int i = 0; i < swaps; i++) {
            int index1 = rand() % n;
            int index2 = rand() % n;
            // Swap elements
            int temp = arr[index1];
            arr[index1] = arr[index2];
            arr[index2] = temp;
        }

        // Measure time for merge sort
        clock_t start_time = clock();
        mergeSort(arr, 0, n - 1);
        clock_t end_time = clock();


        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        printf("k = 2^%d, Time taken: %f seconds\n", k, time_taken);
        //free(arr);(不知道為什麼用free反而會data overflow)

    }

    return 0;
}
