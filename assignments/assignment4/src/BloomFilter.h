#pragma once

#include <array>
#include <functional>
#include <iostream>
#include <vector>

template <typename T, std::size_t N>
class BloomFilter {
   private:
    int filter_size;
    std::vector<bool> filter;
    std::function<std::array<long, N>(T &)> key_function;

   public:
    BloomFilter(int filter_size,
                std::function<std::array<long, N>(T &)> key_function)
        : filter_size(filter_size),
          filter(filter_size, false),
          key_function(key_function) {}

    friend std::ostream &operator<<(std::ostream &os,
                                    const BloomFilter<T, N> &bf) {
        os << "Filter Content: " << std::endl;
        std::string line;
        for (int i = 0; i < bf.filter_size; i++) {
            if (i % 10 == 0) {
                os << i << "-" << i + 10 << ":\t";
            }
            os << bf.filter[i] << " ";
            if ((i + 1) % 10 == 0) {
                os << std::endl;
            }
        }
        os << std::endl;
        return os;
    }

    int key_idx(long key) { return abs(key) % this->filter_size; }

    float fill_ratio() {
        int true_count = 0;
        for (int i = 0; i < this->filter_size; i++) {
            if (this->filter[i]) {
                true_count++;
            }
        }
        return ((float)true_count) / this->filter_size;
    }

    void add(T &item) {
        std::array<long, N> keys = this->key_function(item);
        for (const auto &key : keys) {
            this->filter[this->key_idx(key)] = true;
        }
    }

    bool contains(T &item) {
        std::array<long, N> keys = this->key_function(item);
        for (const long &key : keys) {
            if (!this->filter[this->key_idx(key)]) {
                return false;
            }
        }
        return true;
    }
};
