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

    for (int i = 10; i <= 30; i++) {
        int n = 1 << i; // n=2^i
        int *arr = (int *)malloc(n * sizeof(int));

        // 產生隨機數填充array
        for (int k = 0; k < n; k++) {
            arr[k] = rand() % n;
        }

        // 計時開始
        clock_t start = clock();

        // Hoare Partition 快速排序
        quickSort(arr, 0, n - 1);

        // 計時結束
        clock_t end = clock();
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        // 顯示排序後的數組和執行時間
        printf("i= %d, Execution Time: %f seconds\n", i, cpu_time_used);

        // 釋放記憶體
        free(arr);
    }

    return 0;
}
