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
    srand(time(NULL));  // Seed for random number generation

    int n = 1 << 20;   // Size of the array (2^20)
    clock_t start, end;
    double cpu_time_used;

    for (int k = 0; k <= 20; k++) {
        int *arr = (int *)malloc(n * sizeof(long));

        // Generate array with random values between 0 and k-1
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % (1 << k);
        }

        // Measure the time taken by insertion sort
        start = clock();
        mergeSort(arr, 0, n - 1);
        end = clock();

        // Calculate CPU time used
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("k = %d, Time taken by insertion sort: %f seconds\n", k, cpu_time_used);

        // Free allocated memory
        free(arr);
    }

    return 0;
}
