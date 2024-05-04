#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 交換兩個元素的值
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Hoare Partition
int hoarePartition(int arr[], int low, int high) {
    int pivot = arr[low]; // 選擇第一個元素作為pivot
    int i = low - 1;
    int j = high + 1;

    while (1) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j)
            return j;

        swap(&arr[i], &arr[j]);
    }
}

// 快速排序
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = hoarePartition(arr, low, high);

        quickSort(arr, low, pi);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    srand(time(NULL));

    int n = 1 << 20;  // n=2^20
    int *arr = (int *)malloc(n * sizeof(int)); //int arr[n];

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

        // Measure time for insertion sort
        clock_t start_time = clock();
        quickSort(arr, 0, n-1);
        clock_t end_time = clock();


        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        printf("k = %d, Time taken: %f seconds\n", k, time_taken);

        //free RAM
        free(arr);
    }

    return 0;
}
