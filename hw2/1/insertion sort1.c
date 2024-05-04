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

        // �����H���ƶ�R�Ʋ�
        for (j = 0; j < n; j++) {
            arr[j] = rand() % n;
        }

        // �p�ɶ}�l
        start = clock();

        // ���J�Ƨ�
        insertionSort(arr, n);

        // �p�ɵ���
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        // ��ܱƧǫ᪺�ƲթM����ɶ�
        printf("i = %d, Execution Time: %f seconds\n", i, cpu_time_used);

        // ����ʺA���t���ƲհO����
        free(arr);
    }

    return 0;
}
