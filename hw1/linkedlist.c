#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定義Object結構
struct Object {
    int num;
    int foo[511]; /// k = 1, 7, 63, 511 手動調整
    struct Object* next;
};

// 新增Object到linked list的末端
struct Object* insert(struct Object* head, int num) {
    struct Object* newNode = (struct Object*)malloc(sizeof(struct Object));//取得記憶體空間
    newNode->num = num;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode; // 如果linked list是空的，新節點成為第一個節點
    }

    //初始化Object並插入到linked list末端
    struct Object* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

int main() {
    //設h值，如果跑不動手動調整
    int h_values[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};


    for (int i = 0; i < 21; i++) {
        int n = 1 << h_values[i];
        struct Object* head = NULL;

        // 測量新增(add)時間
        clock_t Start_time = clock();
        // 插入num到linked list
        for (int j = 0; j < n; j++) {
            int num = rand() % 10000;
            head = insert(head, num);
        }
        clock_t End_time = clock();
        double add_time = (double)(End_time - Start_time) / CLOCKS_PER_SEC;


        // 測量加總(sum)時間
        clock_t start_time = clock();
        //計算num的總和
        int sum = 0;
        struct Object* current = head;
        while (current != NULL) {
            sum += current->num;
            current = current->next;
        }
        clock_t end_time = clock();
        double sum_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        //印出實驗結果
        printf("h = %d, Add Time: %f seconds, Sum Time: %f seconds\n", h_values[i], add_time, sum_time);

        // 釋放記憶體空間
        struct Object* temp;
        while (head != NULL) {
            temp = head;
            head = head->next;
            free(temp);
        }
    }

    return 0;
}

