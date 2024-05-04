#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void countingSort(int arr[], int n) {
    int max = 0;

    // ���array�����̤j��
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }


    int* count = (int*)malloc((max + 1) * sizeof(int));
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }

    // �p��C�Ӥ������X�{����
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }


    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // �ЫؼȦsarray�Ω�Ƨ�
    int* result = (int*)malloc(n * sizeof(int));

    // ����counting sort
    for (int i = n - 1; i >= 0; i--) {
        result[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // �ƻs���G�^��array
    for (int i = 0; i < n; i++) {
        arr[i] = result[i];
    }

    // ����RAM
    free(count);
    free(result);
}

int main() {
    srand(time(NULL));

    for (int i = 10; i <= 30; i++) {
        int n = 1 << i;  // array�j�pn=2^i

        int* arr = (int*)malloc(n * sizeof(int));

        // �H���ͦ��Ʋդ���
        for (int k = 0; k < n; k++) {
            arr[k] = rand() % n;
        }

        // �p�ɶ}�l
        clock_t start = clock();

        // counting sort
        countingSort(arr, n);

        // �p�ɵ���
        clock_t end = clock();

        // �p�����ɶ�
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("i= %d, Execution time: %f seconds\n", i, cpu_time_used);

        free(arr);  // ����RAM
    }

    return 0;
}
