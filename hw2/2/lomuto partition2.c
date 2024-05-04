#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Lomuto Partition
int lomutoPartition(int arr[], int low, int high) {
    int pivot = arr[high]; // 選擇最後一個元素作為pivot
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = lomutoPartition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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
        int swaps = 1 << k; //swaps=2^k
        for (int i = 0; i < swaps; i++) {
            int index1 = rand() % n;
            int index2 = rand() % n;
            // Swap elements
            int temp = arr[index1];
            arr[index1] = arr[index2];
            arr[index2] = temp;
        }

        // 計算時間
        clock_t start_time = clock();
        quickSort(arr, 0, n - 1);
        clock_t end_time = clock();

        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        printf("k = 2^%d, Time taken: %f seconds\n", k, time_taken);

        //釋放RAM
        free(arr);
    }


    return 0;
}
