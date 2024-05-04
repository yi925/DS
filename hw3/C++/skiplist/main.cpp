#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <set>
#include <ctime>

class SkipList {
private:
    struct Node {
        int value;
        std::vector<Node*> next;

        Node(int val, int level) : value(val), next(level + 1, nullptr) {}
    };

    Node* head;
    const int MAX_LEVEL = 8;  // 將最大層級減少到 8

public:
    SkipList() : head(new Node(-1, MAX_LEVEL)) {}

    ~SkipList() {
        Node* node = head->next[0];
        while (node) {
            Node* nextNode = node->next[0];
            delete node;
            node = nextNode;
        }
        delete head;
    }

   void insert(int val) {
    if (contains(val)) return;

    int level = getRandomLevel();
    Node* newNode = new(std::nothrow) Node(val, level);
    if (!newNode) {
        std::cerr << "Memory allocation failed!" << std::endl;
        return;
    }

    // 嘗試預留空間
    newNode->next.reserve(level + 1);

    Node* current = head;
    for (int i = MAX_LEVEL; i >= 0; --i) {
        while (current->next[i] && current->next[i]->value < val) {
            current = current->next[i];
        }
        if (i <= level) {
            newNode->next[i] = current->next[i];
            current->next[i] = newNode;
        }
    }
}


    bool contains(int val) {
        Node* current = head;
        for (int i = MAX_LEVEL; i >= 0; --i) {
            while (current->next[i] && current->next[i]->value < val) {
                current = current->next[i];
            }
        }
        current = current->next[0];
        return current && current->value == val;
    }

    std::vector<int> range_query(int a, int b) {
        std::vector<int> result;
        Node* current = head;
        for (int i = MAX_LEVEL; i >= 0; --i) {
            while (current->next[i] && current->next[i]->value < a) {
                current = current->next[i];
            }
        }
        current = current->next[0];
        while (current && current->value <= b) {
            result.push_back(current->value);
            current = current->next[0];
        }
        return result;
    }

private:
    int getRandomLevel() {
        int level = 0;
        while (rand() % 2 && level < MAX_LEVEL) {
            ++level;
        }
        return level;
    }
};

bool equivalent(const std::vector<int>& S1, const std::vector<int>& S2) {
    if (S1.size() != S2.size()) return false;

    std::multiset<int> multiset_S1(S1.begin(), S1.end());
    std::multiset<int> multiset_S2(S2.begin(), S2.end());

    for (int num : multiset_S1) {
        if (multiset_S1.count(num) != multiset_S2.count(num)) {
            return false;
        }
    }
    return true;
}

int main() {
    srand(time(0));

    std::vector<int> numbers;
    const int n = (1 << 5) - 1;
    for (int i = 0; i < n; ++i) {
        numbers.push_back(rand() % n);
    }

    std::ofstream outFile("numbers.txt");
    for (int num : numbers) {
        outFile << num << std::endl;
    }
    outFile.close();

    std::ifstream inFile("numbers.txt");
    int num;
    std::vector<int> readNumbers;
    while (inFile >> num) {
        readNumbers.push_back(num);
    }
    inFile.close();

    SkipList skipList;
    for (int num : readNumbers) {
        skipList.insert(num);
    }

    int a = rand() % n;

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> result = skipList.range_query(a, a + (1 << 5));
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Range query time: " << duration.count() << " microseconds" << std::endl;

    if (equivalent(result, skipList.range_query(a, a + (1 << 20)))) {
        std::cout << "Equivalent: yes" << std::endl;
    } else {
        std::cout << "Equivalent: no" << std::endl;
    }

    return 0;
}

