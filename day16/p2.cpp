#include "lib.hpp"
#include <cstdint>
#include <functional>
#include <iostream>
#include <numeric>
#include <cassert>

std::string calculate(BITSPacBase* p);
std::uint64_t calculate2(BITSPacBase* p);

int main() {
    do {
    BITStream bits;
    std::cin>>bits;
    std::cerr<<bits<<std::endl;
    
    size_t index = 0;
    auto p = parse(bits, index); print(p);

    auto ret = calculate(p.get());
    std::cout<<std::bitset<64>(ret).to_ullong()<<" ("<<ret<<")"<<std::endl;
    std::cout<<calculate2(p.get())<<std::endl;
    } while(!std::cin.eof());

    //std::cout<<add_bits("111000", "1100000000")<<std::endl;
    //std::cout<<add_bits(std::string("110"), std::string("0"))<<std::endl;
    //std::cout<<mul_bits("100", "0100")<<std::endl;
    //std::cout<<(std::string("101")>std::string("0100"))<<std::endl;
    return 0;
}

std::string calculate(BITSPacBase* p) {
    if (p->pack == BITSPacBase::Op) {
        std::vector<std::string> ret;

        for(auto& sp: static_cast<BITSOpPac*>(p)->subpacs) {
            ret.push_back(calculate(sp.get()));
        }

        switch(p->typ.value) {
            case 0: //sum
            return std::accumulate(ret.cbegin(), ret.cend(), std::string("0"), add_bits);
            break;
            case 1: //product
            return std::accumulate(ret.cbegin(), ret.cend(), std::string("1"), mul_bits);
            break;
            case 2: //min
            return *std::min_element(ret.cbegin(), ret.cend());
            break;
            case 3: //max
            return *std::max_element(ret.cbegin(), ret.cend());
            break;
            case 5: //gt
            return ret[0] > ret[1] ? "1" : "0";
            break;
            case 6: //lt
            return ret[0] < ret[1] ? "1" : "0";
            break;
            case 7: //eq
            return ret[0].substr(ret[0].find_first_not_of('0')) == ret[1].substr(ret[1].find_first_not_of('0')) ? "1" : "0";
            break;
            default:
            assert(false);
            break;
        }
    }
    
    if (p->pack == BITSPacBase::Lv) {
        return static_cast<BITSLvPac*>(p)->raw_value;
    }

    std::cerr<<"Encounter inavlid packet!";
    return "";
}


std::uint64_t calculate2(BITSPacBase* p) {
    if (p->pack == BITSPacBase::Op) {
        std::vector<std::uint64_t> ret;

        for(auto& sp: static_cast<BITSOpPac*>(p)->subpacs) {
            ret.push_back(calculate2(sp.get()));
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
    return 0;
}