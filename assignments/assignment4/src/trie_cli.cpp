#include <array>
#include <fstream>
#include <iostream>
#include <queue>

#include "trie.h"

template <std::size_t N>
std::array<char, N> qtoarr(std::queue<char> q) {
    std::array<char, N> arr;
    int k = 0;
    while (!q.empty() && k < N) {
        arr[k] = q.front();
        q.pop();
        k++;
    }
    return arr;
}

int main(int argc, char const *argv[]) {
    assert(argc == 3);
    std::string genome_fp = argv[1];
    std::string search_fp = argv[2];
    std::ifstream genome_data(genome_fp);
    if (!genome_data.is_open()) {
        std::cerr << "Error opening genome file." << std::endl;
        return 1;
    }
    Trie<char, int, 5> kt(strtoarr<5>("GCATN"));
    char c;
    const int s_size = 12;
    std::queue<char> q;
    unsigned int k = 0;
    unsigned int uniques = 0;
    std::array<char, s_size> s;
    while (genome_data.get(c)) {
        k++;
        if (c != '\n') {
            q.push(c);
        }
        if (q.size() == s_size) {
            s = qtoarr<s_size>(q);
            if (!kt.observed(s)) {
                kt.add(s);
                uniques++;
            }
            q.pop();
        }
    }
    genome_data.close();
    std::ifstream search_data(search_fp);
    if (!search_data.is_open()) {
        std::cerr << "Error opening genome file." << std::endl;
        return 1;
    }
    std::string line;
    while (std::getline(search_data, line)) {
        std::cout << kt.observed(strtoarr<s_size>(line)) << std::endl;
    }
    search_data.close();
    return 0;
}