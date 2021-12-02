#include <array>
#include <iostream>
#include <algorithm>

int main() {
    uint count = 0;
    std::array<uint, 3> win{0};
    std::cin>>win[0]>>win[1]>>win[2];
    uint previous = win[0]+win[1]+win[2];
    uint current = 0;

    win[0]=win[1];
    win[1]=win[2];
    do {
        std::cin>>win[2];
        current = win[0]+win[1]+win[2];
        std::cerr<<win[0]<<" "<<win[1]<<" "<<win[2]<<" "<<current<<" "<<previous<<" "<<count<<std::endl;
        if (current > previous)
            count++;
        win[0]=win[1];
        win[1]=win[2];
        previous = current;
    } while(!std::cin.eof());

    std::cout<<count<<std::endl;
    return 0;
}