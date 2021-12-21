#include "lib.hpp"
#include <iostream>

int main() {
    Cavern cave;

    std::cin>>cave;
    std::cerr<<cave<<std::endl;

    int flash_cnt = 0;
    for(int i=0;i<100;i++) {
        flash_cnt+=step1(cave);
    }

    std::cerr<<cave<<std::endl;
    std::cout<<flash_cnt<<std::endl;

    return 0;
}