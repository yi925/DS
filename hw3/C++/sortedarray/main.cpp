#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <set>

class SortedArray {
private:
    std::vector<int> data;

public:
    SortedArray(const std::vector<int>& input) : data(input) {
        std::sort(data.begin(), data.end());
    }

    std::vector<int> range_query(int a, int b) {
        std::vector<int> result;
        for (int i = 0; i < data.size(); ++i) {
            if (data[i] >= a && data[i] <= b) {
                result.push_back(data[i]);
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

    // 4. �s�Jsorted array��Ƶ��c
    SortedArray sortedArray(numbers);

    // 5. �����H��a
    int a = rand() % n;

    // 6. �d��d�ߨô��q�ɶ�
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> result = sortedArray.range_query(a, a + (1 << 20));  // �ϥ�k=2^20
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Range query time: " << duration.count() << " microseconds" << std::endl;

    // 7. �������ˬd
    if (equivalent(result, sortedArray.range_query(a, a + (1 << 20)))) {
        std::cout << "Equivalent: yes" << std::endl;
    } else {
        std::cout << "Equivalent: no" << std::endl;
    }

    return 0;
}
