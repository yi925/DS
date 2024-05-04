#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <set>
#include <cmath>

class ArrayOfSortedArrays {
private:
    std::vector<std::vector<int>> arrays;

public:
    ArrayOfSortedArrays(const std::vector<int>& input) {
        // �w�q�l�}�C���j�p�A�Ҧp�������+1
        const int blockSize = std::sqrt(input.size()) + 1;
        for (int i = 0; i < input.size(); i += blockSize) {
            std::vector<int> block(input.begin() + i, std::min(input.begin() + i + blockSize, input.end()));
            std::sort(block.begin(), block.end());
            arrays.push_back(block);
        }
    }

    std::vector<int> range_query(int a, int b) {
        std::vector<int> result;
        for (const auto& arr : arrays) {
            for (int num : arr) {
                if (num >= a && num <= b) {
                    result.push_back(num);
                }
            }
        }
        return result;
    }
};

bool equivalent(const std::vector<int>& S1, const std::vector<int>& S2) {
    if (S1.size() != S2.size()) return false;

    std::multiset<int> multiset_S1(S1.begin(), S1.end());
    std::multiset<int> multiset_S2(S2.begin(), S2.end());

    // �ˬd�C�Ӥ����b��Ӧh�����X�����W�v�O�_�ۦP
    for (int num : multiset_S1) {
        if (multiset_S1.count(num) != multiset_S2.count(num)) {
            return false;
        }
    }

    return true;
}

void print(const std::vector<int>& S) {
    for (int num : S) {
        std::cout << num << std::endl;
    }
}

int main() {
    // 1. �����H����
    std::vector<int> input;
    const int n = (1 << 20) - 1;
    for (int i = 0; i < n; ++i) {
        input.push_back(rand() % n);
    }

    // 2. �N�Ʀr�s�J��r�ɮפ�
    std::ofstream outFile("numbers.txt");
    for (int num : input) {
        outFile << num << std::endl;
    }
    outFile.close();

    // 3. Ū��
    std::ifstream inFile("numbers.txt");
    int num;
    std::vector<int> numbers;
    while (inFile >> num) {
        numbers.push_back(num);
    }
    inFile.close();

    // 4. �s�JarrayOfSortedArrays��Ƶ��c
    ArrayOfSortedArrays arrayOfSortedArrays(numbers);

    // 5. �����H��a
    int a = rand() % n;

    // 6. �d��d�ߨô��q�ɶ�
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> result = arrayOfSortedArrays.range_query(a, a + (1 << 20));  // �ϥ�k=2^20
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Range query time: " << duration.count() << " microseconds" << std::endl;

    // 7. �������ˬd
    if (equivalent(result, arrayOfSortedArrays.range_query(a, a + (1 << 20)))) {
        std::cout << "Equivalent: yes" << std::endl;
    } else {
        std::cout << "Equivalent: no" << std::endl;
    }

    return 0;
}

