#include <iostream>
#include <map>
#include <chrono>  // 用於計時
#include <random>  // 用於生成隨機數
#include <cmath>

int main()
{
    // 1. 產生一個空的B tree
    std::map<int, int> balancedBST;

    // 2. 新增n筆資料至該B tree，並計算總共花費時間
    for (int k = 10; k <= 30; ++k) {
        const int n = std::pow(2, k);
        std::cout << "k= " << k <<"\n";

        // 生成範圍在1到2^30之間的隨機數
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(1, std::pow(2, 30));

        auto start_time = std::chrono::high_resolution_clock::now();  // 計時開始

        for (int i = 0; i < n; ++i) {
            int random_number = distribution(gen);
            balancedBST[random_number] = random_number;  // key和value都是隨機數
        }

        auto end_time = std::chrono::high_resolution_clock::now();  // 計時結束
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

        std::cout << "Total time for inserting " << n << " elements: " << duration.count() << " seconds\n";
    }

    return 0;
}
