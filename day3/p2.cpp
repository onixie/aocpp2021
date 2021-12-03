#include <algorithm>
#include <bitset>
#include <vector>
#include <iostream>

#ifndef BITSIZE
#define BITSIZE 0
#endif

std::vector<std::bitset<BITSIZE>>::iterator filter(bool co2, uint idx, uint total, std::vector<std::bitset<BITSIZE>>::iterator begin, std::vector<std::bitset<BITSIZE>>::iterator end);
std::bitset<BITSIZE> calculate(bool co2, std::vector<std::bitset<BITSIZE>>& inputs);

int main() {
    std::bitset<BITSIZE> tmp;
    std::vector<std::bitset<BITSIZE>> inputs;
    uint total = 0;

    do {
        std::cin>>tmp;
        if (std::cin.eof())
            break;
        inputs.emplace_back(tmp);
        total++;
    } while (!std::cin.eof());

    std::cerr<<total<<std::endl;
    std::for_each(inputs.cbegin(), inputs.cend(), [](std::bitset<BITSIZE> const& input){
        std::cerr<<input<<std::endl;
    });

    auto inputs2{inputs};
    auto co2_rate = calculate(true, inputs);
    auto oxy_rate = calculate(false, inputs2);

    std::cerr<<oxy_rate<<" "<<co2_rate<<" "<<std::endl;
    std::cout<<oxy_rate.to_ulong()*co2_rate.to_ulong()<<std::endl;
    return 0;
}

std::bitset<BITSIZE> calculate(bool co2, std::vector<std::bitset<BITSIZE>>& inputs) {
    int idx = BITSIZE;

    std::vector<std::bitset<BITSIZE>>::iterator begin = inputs.begin();
    std::vector<std::bitset<BITSIZE>>::iterator new_end = inputs.end();
    do {
        new_end = filter(co2, --idx, new_end - begin, begin, new_end);
        
        std::for_each(begin, new_end, [](std::bitset<BITSIZE> const& input){
            std::cerr<<input<<std::endl;
        });

        if (new_end-inputs.begin()<=1)
            break;
    } while (true);

    return *new_end;
}

std::vector<std::bitset<BITSIZE>>::iterator filter(bool co2, uint idx, uint total, std::vector<std::bitset<BITSIZE>>::iterator begin, std::vector<std::bitset<BITSIZE>>::iterator end) {
    int ones = 0;
    bool bit = co2;
    std::for_each(begin, end, [idx, &ones](std::bitset<BITSIZE> const& input){
        if(input.test(idx))
            ones++;
    });
    std::cerr<<total<<" "<<ones<<std::endl;

    if (ones*2>=total)
        bit = !co2;
    
    return std::remove_if(begin, end, [idx, bit](std::bitset<BITSIZE> const& input) {
        return input.test(idx) != bit;
    });
}