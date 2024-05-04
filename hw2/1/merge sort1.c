#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // �Ы��{�ɼƲ�
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // �ƻs�ƾڨ��{�ɼƲ� L[] �M R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // �X���{�ɼƲը� arr[l..r]
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

    // �N�Ѿl�������q L[] �ƻs�� arr[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // �N�Ѿl�������q R[] �ƻs�� arr[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // ����ʺA���t���{�ɼƲհO����
    free(L);
    free(R);
}

void mergeSort(int arr[], int n) {
    int current_size; // �ثe�l�}�C���j�p
    int left_start;   // ���l�}�C���}�l����

    for (current_size = 1; current_size <= n - 1; current_size = 2 * current_size) {
        for (left_start = 0; left_start < n - 1; left_start += 2 * current_size) {
            int mid = left_start + current_size - 1;

            int right_end = (left_start + 2 * current_size - 1) < (n - 1) ? (left_start + 2 * current_size - 1) : (n - 1);

            // �X�֤l�}�C arr[left_start...mid] �M arr[mid+1...right_end]
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

        // �����H���ƶ�R�Ʋ�
        for (j = 0; j < n; j++) {
            arr[j] = rand() % n;
        }

        // �p�ɶ}�l
        start = clock();

        // �X�ֱƧ�
        mergeSort(arr, n);

        // �p�ɵ���
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        // ��ܱƧǫ᪺�ƲթM����ɶ�
        printf("i = %d, Execution Time: %f seconds\n", i, cpu_time_used);

        // ����O����Ŷ�
        free(arr);
    }

    return 0;
}
