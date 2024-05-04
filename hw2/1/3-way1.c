#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// �洫��ӼƦr�����
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
        int i = low + 1;  // i��ܷ�e���b�ˬd������

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

    for (int i = 10; i <= 30; i++) {
        int n = 1 << i;  // n=2^i

        int* arr = (int*)malloc(n * sizeof(int));

        // �H���ͦ�data��Rarray
        for (int k = 0; k < n; k++) {
            arr[k] = rand() % n;
        }

        // �p�ɶ}�l
        clock_t start = clock();

        // 3-Way Partition�ֳt�Ƨ�
        quicksort(arr, 0, n - 1);

        // �p�ɵ���
        clock_t end = clock();

        // �p�����ɶ�
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("i= %d, Execution time: %f s\n", i, cpu_time_used);

        free(arr);  // ����RAM
    }

    return 0;
}
