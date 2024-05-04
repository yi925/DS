#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// �w�qObject���c
struct Object {
    int num;
    int foo[511]; /// k = 1, 7, 63, 511 ��ʽվ�
};

int main() {
    //�]h�ȡA�p�]���ʤ�ʽվ�
    int h_values[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};

    for (int i = 0; i < 21; i++) {
        int n = 1 << h_values[i];
        struct Object *dynamicArray = (struct Object *)malloc(n * sizeof(struct Object));//���o�O����Ŷ�

        //���q�s�W(add)�ɶ�
        clock_t Start_time = clock();
        // ��l��Object�÷s�Wnum��dynamic array
        for (int j = 0; j < n; j++) {
            dynamicArray[j].num = rand() % 10000;
        }

        clock_t End_time = clock();
        double add_time = (double)(End_time - Start_time) / CLOCKS_PER_SEC;


        // ���q�[�`(sum)�ɶ�
        clock_t start_time = clock();
        // �p��num���`�M
        int sum = 0;
        for (int j = 0; j < n; j++) {
            sum += dynamicArray[j].num;
        }
        clock_t end_time = clock();
        double sum_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        //�L�X���絲�G
        printf("h = %d, Add Time: %f seconds, Sum Time: %f seconds\n", h_values[i], add_time, sum_time);

        //����O����Ŷ�
        free(dynamicArray);
    }

    return 0;
}
