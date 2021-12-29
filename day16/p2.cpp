#include "lib.hpp"
#include <cstdint>
#include <iostream>
#include <numeric>

std::uint64_t calculate(BITSPacBase* p);

int main() {
    BITStream bits;
    std::cin>>bits;
    std::cerr<<bits<<std::endl;
    
    size_t index = 0;
    auto p = parse(bits, index); print(p);

    std::cout<<calculate(p.get())<<std::endl;

    std::cout<<add_bits("111000", "1100000000");
    return 0;
}

std::uint64_t calculate(BITSPacBase* p) {
    if (p->pack == BITSPacBase::Op) {
        std::vector<std::uint64_t> ret;

        for(auto& sp: static_cast<BITSOpPac*>(p)->subpacs) {
            ret.push_back(calculate(sp.get()));
        }

        switch(p->typ.value) {
            case 0: //sum
            return std::accumulate(ret.cbegin(), ret.cend(), 0);
            break;
            case 1: //product
            return std::accumulate(ret.cbegin(), ret.cend(), 1, std::multiplies<std::uint64_t>());
            break;
            case 2: //min
            return *std::min_element(ret.cbegin(), ret.cend());
            break;
            case 3: //max
            return *std::max_element(ret.cbegin(), ret.cend());
            break;
            case 5: //gt
            return ret[0] > ret[1] ? 1 : 0;
            break;
            case 6: //lt
            return ret[0] < ret[1] ? 1 : 0;
            break;
            case 7: //eq
            return ret[0] == ret[1] ? 1 : 0;
            break;
        }
    }
    
    if (p->pack == BITSPacBase::Lv) {
        return static_cast<BITSLvPac*>(p)->value;
    }

    std::cerr<<"Encounter inavlid packet!";
    return -1;
}