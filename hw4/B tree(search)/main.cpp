#include <iostream>
#include <map>
#include <chrono>  // �Ω�p��
#include <random>  // �Ω�ͦ��H����
#include <cmath>

int main()
{
    // 1. ���ͤ@�ӪŪ���Ƶ��c
    std::map<int, int> dataStructure;

    // 2. �s�W n ����ƦܸӸ�Ƶ��c�A�íp���`�@��O�ɶ�
    for (int k = 10; k <= 30; ++k) {
        const int n = std::pow(2, k);
        std::cout << "k= " << k << "\n";

        // �ͦ��d��b 1 �� 2^30 �������H����
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(1, std::pow(2, 30));

        auto start_time = std::chrono::high_resolution_clock::now();  // �p�ɶ}�l

        for (int i = 0; i < n; ++i) {
            int random_number = distribution(gen);
            dataStructure[random_number] = random_number;  // key �M value ���O�H����
        }

        auto end_time = std::chrono::high_resolution_clock::now();  // �p�ɵ���
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

        std::cout << "Total time for inserting " << n << " elements: " << duration.count() << " seconds\n";

        // 3. �b��Ƶ��c���j�M�Q�U����ơA�íp��һݮɶ�
        std::uniform_int_distribution<int> search_distribution(1, std::pow(2, 30));
        auto search_start_time = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 100000; ++i) {
            int random_search_number = search_distribution(gen);
            auto search_result = dataStructure.find(random_search_number);
        }

        auto search_end_time = std::chrono::high_resolution_clock::now();
        auto search_duration = std::chrono::duration_cast<std::chrono::seconds>(search_end_time - search_start_time);

        std::cout << "Total time for searching 100,000 elements: " << search_duration.count() << " seconds\n";
    }

    return 0;
}
