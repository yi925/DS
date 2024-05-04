#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定義Object結構
struct Object {
    int num;
    int foo[511]; /// k = 1, 7, 63, 511 手動調整
};

int main() {
    //設h值，如跑不動手動調整
    int h_values[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};

    for (int i = 0; i < 21; i++) {
        int n = 1 << h_values[i];
        struct Object *dynamicArray = (struct Object *)malloc(n * sizeof(struct Object));//取得記憶體空間

        //測量新增(add)時間
        clock_t Start_time = clock();
        // 初始化Object並新增num到dynamic array
        for (int j = 0; j < n; j++) {
            dynamicArray[j].num = rand() % 10000;
        }

        clock_t End_time = clock();
        double add_time = (double)(End_time - Start_time) / CLOCKS_PER_SEC;


        // 測量加總(sum)時間
        clock_t start_time = clock();
        // 計算num的總和
        int sum = 0;
        for (int j = 0; j < n; j++) {
            sum += dynamicArray[j].num;
        }
        clock_t end_time = clock();
        double sum_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        //印出實驗結果
        printf("h = %d, Add Time: %f seconds, Sum Time: %f seconds\n", h_values[i], add_time, sum_time);

        //釋放記憶體空間
        free(dynamicArray);
    }

    return 0;
}
