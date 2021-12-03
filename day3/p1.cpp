#include <algorithm>
#include <array>
#include <ios>
#include <iostream>
#include <bitset>

#ifndef BITSIZE
#define BITSIZE 12
#endif

int main() {
    std::bitset<BITSIZE> diagnostic_code={};
    std::bitset<BITSIZE> gamma_code={};

    std::array<uint, BITSIZE> ones={};
    int total = 0;
    do {
        std::cin>>diagnostic_code;
        if (std::cin.eof())
            break;

        for(int i=BITSIZE-1;i>=0;i--) {
            if (diagnostic_code.test(i)) 
                ones[i]++;
        }
        total++;
        std::cerr<<diagnostic_code<<std::endl;
    } while(!std::cin.eof());
    
    std::cerr<<total<<" "<<std::endl;
    std::for_each(ones.crbegin(), ones.crend(), [](uint one){
        std::cerr<<one<<",";
    }); std::cerr<<std::endl;

    for(int i=BITSIZE-1;i>=0;i--) {
        if (ones[i]*2>=total)
            gamma_code.set(i);
    }

    auto gamma_rate = gamma_code.to_ulong();
    auto epsilon_rate = gamma_code.flip().to_ulong();

    std::cerr<<gamma_code<<" "<<gamma_rate<<" "<<epsilon_rate<<std::endl;
    
    std::cout<<gamma_rate*epsilon_rate<<std::endl;
    return 0;
}