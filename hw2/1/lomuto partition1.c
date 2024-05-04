#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 交換兩個元素的值
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

// 快速排序
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = lomutoPartition(arr, low, high);

        quickSort(arr, low, pi - 1);
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

        // Lomuto Partition 快速排序
        quickSort(arr, 0, n - 1);

        // 計時結束
        clock_t end = clock();
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        // 顯示排序後的數組和執行時間
        printf("i = %d, Execution Time: %f seconds\n", i, cpu_time_used);

        // 釋放記憶體
        free(arr);
    }

    return 0;
}
