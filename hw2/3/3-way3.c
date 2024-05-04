#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 3-Way Partition的快速排序
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int lt = low;    // lt表示小於pivot的區域的右邊界
        int gt = high;   // gt表示大於pivot的區域的左邊界
        int i = low + 1;  // i表示正在檢查的元素

        int pivot = arr[low];  // 使用第一個元素作為pivot

        while (i <= gt) {
            if (arr[i] < pivot) {
                swap(&arr[i], &arr[lt]);
                lt++;
                i++;
            } else if (arr[i] > pivot) {
                swap(&arr[i], &arr[gt]);
                gt--;
            } else {
                i++;
            }
        }

        // 遞歸處理小於和大於pivot的兩個區域
        quickSort(arr, low, lt - 1);
        quickSort(arr, gt + 1, high);
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
        quickSort(arr, 0, n - 1);
        end = clock();


        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("k = %d, Time taken by insertion sort: %f seconds\n", k, cpu_time_used);

        // Free allocated memory
        free(arr);
    }

    return 0;
}
