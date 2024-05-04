#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void countingSort(int arr[], int n) {
    int max = 0;

    // 找到數組中的最大值
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    // 初始化
    int* count = (int*)malloc((max + 1) * sizeof(int));
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }

    // 計算每個元素的出現次數
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // 將計數數組轉換為前綴和
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // 創建暫存array用於排序
    int* result = (int*)malloc(n * sizeof(int));

    // 執行counting sort
    for (int i = n - 1; i >= 0; i--) {
        result[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // 複製結果回原array
    for (int i = 0; i < n; i++) {
        arr[i] = result[i];
    }

    // 釋放RAM
    free(count);
    free(result);
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
        countingSort(arr, n);
        end = clock();


        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("k = %d, Time taken by insertion sort: %f seconds\n", k, cpu_time_used);

        // Free allocated memory
        free(arr);
    }

    return 0;
}
