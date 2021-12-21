#include "lib.hpp"
#include <iostream>

int main() {
    Cavern cave;

    std::cin>>cave;
    std::cerr<<cave<<std::endl;

    int total_octs = cave.octs.size() * cave.octs[0].size();
    int s=0;
    do {
        s++;
    } while (step1(cave) != total_octs);

    std::cerr<<cave<<std::endl;
    std::cout<<s<<std::endl;

    return 0;
}