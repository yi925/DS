#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void countingSort(int arr[], int n) {
    int max = 0;

    // 找到array中的最大值
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }


    int* count = (int*)malloc((max + 1) * sizeof(int));
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }

    // 計算每個元素的出現次數
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }


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
    srand(time(NULL));

    for (int i = 10; i <= 30; i++) {
        int n = 1 << i;  // array大小n=2^i

        int* arr = (int*)malloc(n * sizeof(int));

        // 隨機生成數組元素
        for (int k = 0; k < n; k++) {
            arr[k] = rand() % n;
        }

        // 計時開始
        clock_t start = clock();

        // counting sort
        countingSort(arr, n);

        // 計時結束
        clock_t end = clock();

        // 計算執行時間
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("i= %d, Execution time: %f seconds\n", i, cpu_time_used);

        free(arr);  // 釋放RAM
    }

    return 0;
}
