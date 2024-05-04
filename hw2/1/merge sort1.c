#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // 創建臨時數組
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // 複製數據到臨時數組 L[] 和 R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // 合併臨時數組到 arr[l..r]
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

    // 將剩餘的元素從 L[] 複製到 arr[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // 將剩餘的元素從 R[] 複製到 arr[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // 釋放動態分配的臨時數組記憶體
    free(L);
    free(R);
}

void mergeSort(int arr[], int n) {
    int current_size; // 目前子陣列的大小
    int left_start;   // 左子陣列的開始索引

    for (current_size = 1; current_size <= n - 1; current_size = 2 * current_size) {
        for (left_start = 0; left_start < n - 1; left_start += 2 * current_size) {
            int mid = left_start + current_size - 1;

            int right_end = (left_start + 2 * current_size - 1) < (n - 1) ? (left_start + 2 * current_size - 1) : (n - 1);

            // 合併子陣列 arr[left_start...mid] 和 arr[mid+1...right_end]
            merge(arr, left_start, mid, right_end);
        }
    }
}

int main() {
    int i, j;
    clock_t start, end;
    double cpu_time_used;

    for (i = 10; i <= 30; i++) {
        int n = 1 << i; // n=2^i
        int *arr = (int *)malloc(n * sizeof(int));

        if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
        }

        // 產生隨機數填充數組
        for (j = 0; j < n; j++) {
            arr[j] = rand() % n;
        }

        // 計時開始
        start = clock();

        // 合併排序
        mergeSort(arr, n);

        // 計時結束
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        // 顯示排序後的數組和執行時間
        printf("i = %d, Execution Time: %f seconds\n", i, cpu_time_used);

        // 釋放記憶體空間
        free(arr);
    }

    return 0;
}
