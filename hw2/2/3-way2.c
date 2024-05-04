#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 3-Way Partition���ֳt�Ƨ�
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int lt = low;    // lt��ܤp��pivot���ϰ쪺�k���
        int gt = high;   // gt��ܤj��pivot���ϰ쪺�����
        int i = low + 1;  // i��ܥ��b�ˬd������

        int pivot = arr[low];  // �ϥβĤ@�Ӥ����@��pivot

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

        // ���k�B�z�p��M�j��pivot����Ӱϰ�
        quicksort(arr, low, lt - 1);
        quicksort(arr, gt + 1, high);
    }
}


int main() {
    srand(time(NULL));

    int n = 1 << 20;  // 2^20
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

        // Measure time for quick sort
        clock_t start_time = clock();
        quicksort(arr, 0, n-1);
        clock_t end_time = clock();


        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        printf("k = %d, Time taken: %f seconds\n", k, time_taken);

        free(arr);
    }

    return 0;
}
