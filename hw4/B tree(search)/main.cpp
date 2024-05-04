#include <iostream>
#include <map>
#include <chrono>  // 用於計時
#include <random>  // 用於生成隨機數
#include <cmath>

int main()
{
    // 1. 產生一個空的資料結構
    std::map<int, int> dataStructure;

    // 2. 新增 n 筆資料至該資料結構，並計算總共花費時間
    for (int k = 10; k <= 30; ++k) {
        const int n = std::pow(2, k);
        std::cout << "k= " << k << "\n";

        // 生成範圍在 1 到 2^30 之間的隨機數
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(1, std::pow(2, 30));

        auto start_time = std::chrono::high_resolution_clock::now();  // 計時開始

        for (int i = 0; i < n; ++i) {
            int random_number = distribution(gen);
            dataStructure[random_number] = random_number;  // key 和 value 都是隨機數
        }

        auto end_time = std::chrono::high_resolution_clock::now();  // 計時結束
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

        std::cout << "Total time for inserting " << n << " elements: " << duration.count() << " seconds\n";

        // 3. 在資料結構中搜尋十萬筆資料，並計算所需時間
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
