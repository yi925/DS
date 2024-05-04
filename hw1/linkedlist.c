#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// �w�qObject���c
struct Object {
    int num;
    int foo[511]; /// k = 1, 7, 63, 511 ��ʽվ�
    struct Object* next;
};

// �s�WObject��linked list������
struct Object* insert(struct Object* head, int num) {
    struct Object* newNode = (struct Object*)malloc(sizeof(struct Object));//���o�O����Ŷ�
    newNode->num = num;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode; // �p�Glinked list�O�Ū��A�s�`�I�����Ĥ@�Ӹ`�I
    }

    //��l��Object�ô��J��linked list����
    struct Object* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

int main() {
    //�]h�ȡA�p�G�]���ʤ�ʽվ�
    int h_values[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};


    for (int i = 0; i < 21; i++) {
        int n = 1 << h_values[i];
        struct Object* head = NULL;

        // ���q�s�W(add)�ɶ�
        clock_t Start_time = clock();
        // ���Jnum��linked list
        for (int j = 0; j < n; j++) {
            int num = rand() % 10000;
            head = insert(head, num);
        }
        clock_t End_time = clock();
        double add_time = (double)(End_time - Start_time) / CLOCKS_PER_SEC;


        // ���q�[�`(sum)�ɶ�
        clock_t start_time = clock();
        //�p��num���`�M
        int sum = 0;
        struct Object* current = head;
        while (current != NULL) {
            sum += current->num;
            current = current->next;
        }
        clock_t end_time = clock();
        double sum_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        //�L�X���絲�G
        printf("h = %d, Add Time: %f seconds, Sum Time: %f seconds\n", h_values[i], add_time, sum_time);

        // ����O����Ŷ�
        struct Object* temp;
        while (head != NULL) {
            temp = head;
            head = head->next;
            free(temp);
        }
    }

    return 0;
}

