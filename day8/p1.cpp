#include "lib.hpp"
#include <iostream>
#include <algorithm>

int main() {
    Experiment exp;
    size_t count = 0;
    do {
    std::cin>>exp;
    std::array<Display, 4>const & digits = std::get<1>(exp);
    count += std::count_if(digits.cbegin(), digits.cend(), [](auto digit){
        switch (digit.length()) {
            case 2: //1
            case 4: //4
            case 3: //7
            case 7: //8
            return true;
        }
        return false;
    });
    std::cerr<<exp<<std::endl;
    } while (!std::cin.eof());

    std::cout<<count<<std::endl;
    return 0;
}