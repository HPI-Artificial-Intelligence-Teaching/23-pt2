#include <doctest.h>

#include <cmath>
#include <map>
#include <random>
#include <string>
#include <vector>

#include "../src/BloomFilter.h"
#include "../src/hash.h"
#include "../src/random_string.cpp"

TEST_CASE("A1.2: Bloom Filter") {
    std::string s = "Hello, World!";
    BloomFilter<std::string, 5> bf(8191, hash_key<std::string, 5>);
    SUBCASE("A1.2a: Add") {
        bf.add(s);
        CHECK(bf.fill_ratio() != doctest::Approx(0));
    }
    SUBCASE("A1.2b: Contains") {
        bf.add(s);
        CHECK(bf.contains(s));
    }
}

TEST_CASE("A1: Saturation") {
    BloomFilter<std::string, 5> bf(293, hash_key<std::string, 5>);
    for (int i = 0; i < 100; i++) {
        std::string s = random_string(25, i);
        bf.add(s);
    }
    MESSAGE("Fill Ratio: ", bf.fill_ratio());
}

TEST_CASE("A1.1a: Gleichverteilung der Hashfunktion") {
    const int num_keys = 50000;
    const int num_buckets = 293;
    std::map<int, int> bucket_counts;
    std::function<std::array<long, 1>(std::string)> hash_key =
        make_hash_key_mult<std::string, 1>();
    for (int i = 0; i < num_keys; i++) {
        int key = i;
        for (long k : hash_key(std::to_string(key))) {
            int bucket = k % num_buckets;
            if (bucket < 0) {
                bucket += num_buckets;
            }
            bucket_counts[bucket]++;
        }
    }
    double chi_square = 0.0;
    int expected = num_keys / num_buckets;
    for (const auto& pair : bucket_counts) {
        chi_square += pow(pair.second - expected, 2) / expected;
    }
    /*
    if chi_square value is below the critical value, the test passes
    meaning that the histogram is not significantly different from a uniform
    distribution (which is what we want)
    */
    CHECK(chi_square < 332.85381);
}