#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 交換兩個數字的函數
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 3-Way Partition的快速排序
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int lt = low;    // lt表示小於pivot的區域的右邊界
        int gt = high;   // gt表示大於pivot的區域的左邊界
        int i = low + 1;  // i表示當前正在檢查的元素

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
        quicksort(arr, low, lt - 1);
        quicksort(arr, gt + 1, high);
    }
}

int main() {
    srand(time(NULL));

    for (int i = 10; i <= 30; i++) {
        int n = 1 << i;  // n=2^i

        int* arr = (int*)malloc(n * sizeof(int));

        // 隨機生成data填充array
        for (int k = 0; k < n; k++) {
            arr[k] = rand() % n;
        }

        // 計時開始
        clock_t start = clock();

        // 3-Way Partition快速排序
        quicksort(arr, 0, n - 1);

        // 計時結束
        clock_t end = clock();

        // 計算執行時間
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("i= %d, Execution time: %f s\n", i, cpu_time_used);

        free(arr);  // 釋放RAM
    }

    return 0;
}
