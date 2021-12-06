#include "lib.hpp"
#include <algorithm>

void simulate(SchoolOfFish& school);
size_t estimate(size_t days);

int main(int argc, char** argv) {
    int days = 0;
    if (argc > 1)
        days = std::stoi(argv[1]);

    SchoolOfFish school{8};
    //std::cin>>school;
    std::cerr<<school<<std::endl;

    int cycle = days;
    while(cycle-- > 0) {
        simulate(school);
        #ifdef DEBUG
        std::cerr<<school<<std::endl;
        #endif
    }
    std::cerr<<school.size()<<std::endl;

    std::cout<<estimate(days)+1<<std::endl;
    return 0;
}

size_t estimate(size_t days) {
    if (days >= 9) {
        int first_breed = 1; // 9/9
        int rest_breed = (days - 9)/7;
        int breed_estimate = estimate(days - 9); // breed of first breed
        days = days - 9;
        while (days/7 > 0) {
            breed_estimate += estimate(days - 7); // breed of rest breeds
            days = days - 7;
        }
        return first_breed+rest_breed+breed_estimate;
    }
    return 0;
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