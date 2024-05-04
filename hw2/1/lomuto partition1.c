#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// �洫��Ӥ�������
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Lomuto Partition
int lomutoPartition(int arr[], int low, int high) {
    int pivot = arr[high]; // ��̫ܳ�@�Ӥ����@��pivot
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

// �ֳt�Ƨ�
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

        // �����H���ƶ�Rarray
        for (int k = 0; k < n; k++) {
            arr[k] = rand() % n;
        }

        // �p�ɶ}�l
        clock_t start = clock();

        // Lomuto Partition �ֳt�Ƨ�
        quickSort(arr, 0, n - 1);

        // �p�ɵ���
        clock_t end = clock();
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        // ��ܱƧǫ᪺�ƲթM����ɶ�
        printf("i = %d, Execution Time: %f seconds\n", i, cpu_time_used);

        // ����O����
        free(arr);
    }

    return 0;
}
