#include "lib.hpp"
#include <algorithm>
#include <limits>
#include <unordered_map>
#include <stdint.h>

using Cache = std::unordered_map<int, size_t>;
void simulate(SchoolOfFish& school);
size_t estimate(int days, int init_remain, Cache& cache);
inline int encode(int days, int init_remain);

int main(int argc, char** argv) {
    int days = 0;
    if (argc > 1)
        days = std::stoi(argv[1]);

    SchoolOfFish school{};
    std::cin>>school;
    std::cerr<<school<<std::endl;
    Cache cache;
    size_t population = 0;
    for(auto f : school) {
        int key = encode(days, f+1);
        size_t brd = 0;
        if (cache.find(key) == cache.end()) {
            brd=estimate(days, f+1, cache)+1;
            cache[key] = brd;
        } else {
            brd = cache[key];
        }
        population+=brd;
    }

    // int cycle = days;
    // while(cycle-- > 0) {
    //     simulate(school);
    //     #ifdef DEBUG
    //     std::cerr<<school<<std::endl;
    //     #endif
    // }
    // std::cerr<<school.size()<<std::endl;

    std::cout<<population<<std::endl;
    return 0;
}

inline int encode(int days, int init_remain) {
    return days*10+init_remain;
}

size_t estimate(int days, int init_remain, Cache& cache) {
    int key = encode(days, init_remain);
    if (cache.find(key) != cache.end())
        return cache[key];

    days = days - init_remain;
    if (days < 0)
        return 0ULL;
    size_t breed = 1ULL;
    size_t breed_breed = estimate(days, 9, cache);
    breed += breed_breed;
    key = encode(days, 9);
    cache[key] = breed_breed;
    do {
        days = days - 7;

        if (days < 0)
            return breed;

        breed++;
        breed_breed=estimate(days, 9, cache);
        breed += breed_breed;
        key = encode(days, 9);
        cache[key] = breed_breed;
    } while(true);
}

void simulate(SchoolOfFish& school) {
    uint nfc = 0;
    for(auto& f : school) {
        if (f == 0) {
            nfc++;
            f = 6;
        }
        else if (f > 0) {
            f--;
        }
    }

    std::fill_n(std::back_inserter(school), nfc, 8);
}