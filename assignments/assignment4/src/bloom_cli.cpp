#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>

#include "BloomFilter.h"
#include "hash.h"

template <typename T>
void printQ(std::queue<T> Q) {
    while (!Q.empty()) {
        std::cout << Q.front();
        Q.pop();
    }
    std::cout << std::endl;
}

std::string qtostr(std::queue<char> q) {
    std::string s;
    while (!q.empty()) {
        s += q.front();
        q.pop();
    }
    return s;
}

int main(int argc, char **argv) {
    std::string filename = argv[1];
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }
    std::queue<char> q;
    std::string s;
    char c;
    BloomFilter<std::string, 3> bf(250000000, hash_key<std::string, 3>);
    unsigned int k = 0;
    unsigned int uniques = 0;
    while (file.get(c)) {
        k++;
        if (c != '\n') {
            q.push(c);
        }
        if (q.size() == 12) {
            s = qtostr(q);
            if (!bf.contains(s)) {
                bf.add(s);
                uniques++;
            }
            q.pop();
        }
    }
    std::cout << uniques << std::endl;
}