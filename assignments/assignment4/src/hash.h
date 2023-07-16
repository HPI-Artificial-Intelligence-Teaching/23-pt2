#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <string>

template <typename T, std::size_t N>
std::array<long, N> hash_key(const T& a) {
    std::array<long, N> vs;
    vs[0] = static_cast<long>(std::hash<T>{}(a));
    for (std::size_t i = 1; i < N; i++) {
        vs[i] = static_cast<long>(std::hash<long>{}(vs[i - 1]));
    }
    return vs;
}

#include <iostream>
#include <string>
#include <vector>

bool is_prime(unsigned int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;

    if (n % 2 == 0 || n % 3 == 0) return false;

    for (unsigned int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }

    return true;
}

unsigned int find_next_prime(unsigned int n) {
    while (!is_prime(n)) n++;
    return n;
}

template <typename T>
unsigned int multiplikative_hash(const T& str, unsigned int multiplier) {
    unsigned int hash = 0;
    for (const auto& i : str) {
        hash = hash * multiplier + +static_cast<int>(i);
    }
    return hash;
}

template <typename T, std::size_t N>
std::function<std::array<long, N>(const T& a)> make_hash_key_mult(
    int base_multiplier = 31) {
    assert(N > 0);
    std::array<int, N> multipliers;
    multipliers[0] = base_multiplier;
    for (size_t i = 0; i < N; ++i) {
        multipliers[i] = find_next_prime(multipliers[i - 1] + 1);
    }
    return [&multipliers](const T& a) {
        std::array<long, N> vs;
        vs[0] = multiplikative_hash(a, multipliers[0]);
        for (size_t i = 1; i < N; i++) {
            vs[i] = multiplikative_hash<T>(a, multipliers[i]);
        }
        return vs;
    };
}
