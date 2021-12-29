#include "lib.hpp"
#include <cstdint>
#include <functional>
#include <iostream>
#include <numeric>
#include <cassert>
#include <ostream>
#include <string>
#include <sstream>

std::string calculate(BITSPacBase* p);
std::uint64_t calculate2(BITSPacBase* p);
std::string translate(BITSPacBase* p);

int main() {
    do {
    BITStream bits;
    std::cin>>bits;
    std::cerr<<bits<<std::endl;
    
    size_t index = 0;
    auto p = parse(bits, index); //print(p);

    std::cout<<translate(p.get())<<std::endl; // feed output expr to https://ideone.com/
    auto ret = calculate(p.get());
    std::cout<<std::bitset<64>(ret).to_ullong()<<" ("<<ret<<")"<<std::endl;
    std::cout<<calculate2(p.get())<<std::endl;
    } while(!std::cin.eof());

    return 0;
}

std::string translate(BITSPacBase* p) {
    if (p->pack == BITSPacBase::Op) {
        std::vector<std::string> ret;

        for(auto& sp: static_cast<BITSOpPac*>(p)->subpacs) {
            ret.push_back(translate(sp.get()));
        }

        std::string s;
        switch(p->typ.value) {
            case 0: {//sum 
            s="(+"; 
            break;
            }
            case 1: {//product
            s="(*"; 
            break;
            }
            case 2: {//min
            s="(min"; 
            break;
            }
            case 3: {//max
            s="(max"; 
            break;
            }
            case 5: {//gt
            s="(if (>";
            break;
            }
            case 6: {//lt
            s="(if (<";
            break;
            }
            case 7: {//eq
            s="(if (=";
            break;
            }
            default:
            assert(false);
        }
        for(auto& v:ret) s+=" "+v;
        switch(p->typ.value) {
            case 5: //gt
            case 6: //lt
            case 7: {//eq
            s+=") 1 0)";
            break;
            }
            default:
            s+=")";
            break;
        }
        return s;
    }
    
    if (p->pack == BITSPacBase::Lv) {
        std::stringstream ss; std::string v;
        ss<<static_cast<BITSLvPac*>(p)->value;
        ss>>v;
        return v;
    }

    std::cerr<<"Encounter inavlid packet!"<<std::endl;
    assert(false);
    return "";
}

std::string calculate(BITSPacBase* p) { // fixme: what is wrong?
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

std::uint64_t calculate2(BITSPacBase* p) { // fixme: integer overflow?
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