#include "lib.hpp"
#include <algorithm>

void simulate(SchoolOfFish& school, int days);

int main(int argc, char** argv) {
    uint cycle = 0;
    if (argc > 1)
        cycle = std::stoi(argv[1]);

    SchoolOfFish school;
    std::cin>>school;
    std::cerr<<school<<std::endl;

    simulate(school, cycle);

    //std::cerr<<school<<std::endl;
    std::cout<<school.size()<<std::endl;
    return 0;
}

void simulate(SchoolOfFish& school, int days) {
    if (days > 0) {

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

        #ifdef DEBUG
        std::cerr<<school<<std::endl;
        #endif

        simulate(school, --days);
    }
}