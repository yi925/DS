#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int i, j;
    clock_t start, end;
    double cpu_time_used;

    for (i = 10; i <= 30; i++) {
        int n = 1 << i; // n-2^i
        int *arr = (int *)malloc(n * sizeof(int));

        // 產生隨機數填充數組
        for (j = 0; j < n; j++) {
            arr[j] = rand() % n;
        }

        // 計時開始
        start = clock();

        // 插入排序
        insertionSort(arr, n);

        // 計時結束
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        // 顯示排序後的數組和執行時間
        printf("i = %d, Execution Time: %f seconds\n", i, cpu_time_used);

        // 釋放動態分配的數組記憶體
        free(arr);
    }

    return 0;
}
