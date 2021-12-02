#include <array>
#include <iostream>

int main() {
    uint count = 0;
    uint previous = 0;
    uint current  = 0;
    std::cin>>previous;
    do {
        std::cin>>current;
        std::cerr<<current<<" "<<previous<<" "<<count<<std::endl;
        if (current > previous)
            count++;
        previous = current;
    } while (!std::cin.eof());

    std::cout<<count<<std::endl;
    return 0;
}