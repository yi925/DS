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

    // ��l��
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

    int n = 1 << 20;  // n=2^20
    int *arr = (int *)malloc(n * sizeof(int)); //int arr[n];

    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }

    for (int k = 0; k <= 20; k++) {
        // Randomly swap array elements k times
        int swaps = 1 << k;
        for (int i = 0; i < swaps; i++) {
            int index1 = rand() % n;
            int index2 = rand() % n;
            // Swap elements
            int temp = arr[index1];
            arr[index1] = arr[index2];
            arr[index2] = temp;
        }

        // Measure time for counting sort
        clock_t start_time = clock();
        countingSort(arr, n);
        clock_t end_time = clock();


        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        printf("k = %d, Time taken: %f seconds\n", k, time_taken);

        free(arr);
    }

    return 0;
}
