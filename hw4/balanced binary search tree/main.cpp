#include <iostream>
#include <map>
#include <chrono>  // �Ω�p��
#include <random>  // �Ω�ͦ��H����
#include <cmath>

int main()
{
    // 1. ���ͤ@�ӪŪ�B tree
    std::map<int, int> balancedBST;

    // 2. �s�Wn����Ʀܸ�B tree�A�íp���`�@��O�ɶ�
    for (int k = 10; k <= 30; ++k) {
        const int n = std::pow(2, k);
        std::cout << "k= " << k <<"\n";

        // �ͦ��d��b1��2^30�������H����
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(1, std::pow(2, 30));

        auto start_time = std::chrono::high_resolution_clock::now();  // �p�ɶ}�l

        for (int i = 0; i < n; ++i) {
            int random_number = distribution(gen);
            balancedBST[random_number] = random_number;  // key�Mvalue���O�H����
        }

        auto end_time = std::chrono::high_resolution_clock::now();  // �p�ɵ���
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

        std::cout << "Total time for inserting " << n << " elements: " << duration.count() << " seconds\n";
    }

    return 0;
}
