#include "lib.hpp"
#include <iostream>

int main() {
    Experiment exp;

    do {
    std::cin>>exp;

    std::cerr<<exp<<std::endl;
    } while (!std::cin.eof());
    return 0;
}