#include "lib.hpp"
#include <cstdint>
#include <ios>
#include <bitset>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <iomanip>
#include <cassert>

std::istream& operator>>(std::istream& in, BITStream& stream){
    do {
        char lb, hb;
        lb=in.get();
        if (in.eof() || lb == '\n' || lb == '\r')
            return in;
        hb=in.get();
        if (in.eof() || hb == '\n' || hb == '\r')
            return in;
        std::string s = {lb, hb};
        auto n = 0xFFUL&std::stoul(s, 0, 16);
        stream.push_back(n);
    } while (!in.eof());
    return in;
}

std::ostream& operator<<(std::ostream& out, BITStream const& stream) {
    out<<"hex: ";
    for(auto hex: stream) {
        out<<std::setw(2)<<std::setfill('0')<<std::hex<<(0xFF&hex);
    }
    out<<", bin: ";
    for(auto bin: stream) {
        out<<std::bitset<8>(0xFF&bin)<<" ";
    }
    return out;
}

BITStream operator<<(BITStream const &stream, size_t shift) {
    static constexpr auto store_size = sizeof(BITStream::value_type) * 8;
    BITStream res;
    
    // cut off multiple of store_size
    BITStream::iterator::difference_type cutoff = shift / store_size;
    std::copy(stream.cbegin()+cutoff, stream.cend(), std::back_inserter(res));
    
    // bit shift the rest
    auto left = shift % store_size;
    for(auto iter = res.begin(); iter < res.end(); iter++) {
        *iter = *iter<<left;
        if (iter + 1 < res.end())
            *iter |= *(iter+1)>>(store_size-left);
    }

    return res;
}

inline std::unique_ptr<BITSPacBase> parse(BITStream const& stream, size_t& index) {
    size_t idx = index;
    std::string ret;
    auto op = std::make_unique<BITSOpPac>();
    auto lv = std::make_unique<BITSLvPac>();

    ret = (*lv)(stream, idx);
    if (!ret.empty()) {
        index = idx;
        return std::move(lv);
    }

    ret = (*op)(stream, idx);
    if (!ret.empty()) {
        index = idx;
        return std::move(op);
    }

    return {};
}

void print(std::unique_ptr<BITSPacBase>& pac, std::ostream& out){
    switch(pac->pack) {
        case BITSPacBase::Lv:
        out<<*static_cast<BITSLvPac*>(pac.get());
        break;
        case BITSPacBase::Op:
        out<<*static_cast<BITSOpPac*>(pac.get());
        break;
    }
}

std::string BITSLvPac::operator()(BITStream const& stream, size_t& index) {
    size_t idx=index;

    bits+=ver(stream, idx).to_string();
    bits+=typ(stream, idx).to_string();

    if (typ.value == 4) {
        BITSLit lit;
        do {
            auto l = lit(stream, idx);
            bits+=l.to_string();
            raw_value+=l.to_string().substr(1);
            value = (value<<4) + (0x0F&lit.value);
            if (!l.test(4))
                break;
        } while (true);

        index = idx;
        pack = Lv;

        assert(bits.length() < 57);
        return bits;
    } else {
        bits="";
        return std::string();
    }
}

std::string BITSOpPac::operator()(BITStream const& stream, size_t& index) {
    size_t idx = index;
    bits+=ver(stream, idx).to_string();
    bits+=typ(stream, idx).to_string();

    if (typ.value != 4) {
        bits+=mod(stream, idx).to_string();
        if (mod.value == 1) {
            // num of subpacket
            BITS<std::int32_t, 11> len;
            bits+=len(stream, idx).to_string();
            while (len.value-->0) {
                auto ret = parse(stream, idx);
                if (ret != NULL) {
                    bits+=ret->bits;
                    subpacs.push_back(std::move(ret));
                }
            }
        } else {
            // num of bits
            BITS<std::uint32_t, 15> len;
            bits+=len(stream, idx).to_string();
            while (len.value>0) {
                size_t i = idx;
                auto ret = parse(stream, i);
                if (ret != NULL) {
                    bits+=ret->bits;
                    len.value -= (i - idx);
                    idx = i;
                    subpacs.push_back(std::move(ret));
                }
            }
        }

        pack = Op;
        index = idx;
        return bits;
    } else {
        bits = "";
        return std::string();
    }
}

std::ostream& operator<<(std::ostream& out, BITSLvPac const& pac) {
    out<<"bin: "<<pac.bits<<std::endl;
    out<<"version: "<<std::dec<<pac.ver.value<<std::endl;
    out<<"type: "<<std::dec<<pac.typ.value<<std::endl;
    out<<"value: "<<std::dec<<pac.value<<" ("<<pac.raw_value<<")"<<std::endl;
    return out;
}
std::ostream& operator<<(std::ostream& out, BITSOpPac const& pac) {
    std::stringstream ss;
    out<<"bin: "<<pac.bits<<std::endl;
    out<<"version: "<<std::dec<<pac.ver.value<<std::endl;
    out<<"type: "<<std::dec<<pac.typ.value<<std::endl;
    out<<"mode: "<<std::dec<<pac.mod.value<<std::endl;
    out<<"length: "<<std::dec<<pac.subpacs.size()<<std::endl;
    out<<">>> sub packets >>>"<<std::endl;
    for(auto& sp : pac.subpacs) {
        switch(sp->pack) {
            case BITSPacBase::Lv:
            out<<*static_cast<BITSLvPac*>(sp.get());
            break;
            case BITSPacBase::Op:
            out<<*static_cast<BITSOpPac*>(sp.get());
            break;
            default:
            out<<"Inavlid packets!";
            break;
        }
        out<<std::endl;
    }
    out<<"<<< sub packets <<<"<<std::endl;
    
    return out;
}

std::string add_bits(std::string const& bits1, std::string const& bits2) {
    if (bits1.empty())
        return bits2;

    if (bits2.empty())
        return bits1;

    std::stringstream ss;
    auto b1 = bits1.crbegin();
    auto b2 = bits2.crbegin();
    int c = 0;
    while(b1 < bits1.crend() || b2 < bits2.crend()) {
        int n1 = 0; 
        int n2 = 0;

        if (b1 < bits1.crend()) {
            n1 = *b1 - '0';
            b1++;
        }
        if (b2 < bits2.crend()) {
            n2 = *b2 - '0';
            b2++;
        }

        int s = n1+n2+c;
        c = (0x2&s)>>1;
        s=0x1&s;

        ss<<s;
    }

    if (c) ss<<c;
    std::string s="";
    ss>>s;
    std::reverse(s.begin(), s.end());
    return s;
}

std::string mul_bits(std::string const& bits1, std::string const& bits2) {
    auto b2 = bits2.crbegin();
    std::string sum="0";
    while(b2 < bits2.crend()) {
        if (*b2 - '0') {
            auto shift = std::llabs(std::distance(bits2.crbegin(),b2));
            std::string part = bits1 + std::string(shift, '0');
            sum = add_bits(sum, part);
        }
        b2++;
    }
    return sum;
}

// bool operator==(std::string const& bits1, std::string const& bits2) {
//     // if (bits1.end() - (bits1.begin()+bits1.find_first_not_of('0')) > bits2.end() - (bits2.begin()+bits2.find_first_not_of('0')))
//     //     return false;

//     // if (bits1.end() - (bits1.begin()+bits1.find_first_not_of('0')) < bits2.end() - (bits2.begin()+bits2.find_first_not_of('0')))
//     //     return false;

//     return bits1.substr(bits1.find_first_not_of('0')) == bits2.substr(bits2.find_first_not_of('0'));
// }

bool operator<(std::string const& bits1, std::string const& bits2) {
    return bits2>bits1;
}

bool operator>(std::string const& bits1, std::string const& bits2) {
    if (bits1.end() - (bits1.begin()+bits1.find_first_not_of('0')) > bits2.end() - (bits2.begin()+bits2.find_first_not_of('0')))
        return true;
    
    if (bits1.end() - (bits1.begin()+bits1.find_first_not_of('0')) < bits2.end() - (bits2.begin()+bits2.find_first_not_of('0')))
        return false;

    auto b1 = bits1.cbegin()+bits1.find_first_not_of('0');
    auto b2 = bits1.cbegin()+bits2.find_first_not_of('0');

    while(b1 < bits1.end() || b2 < bits2.end()) {
        if (*b1 > *b2)
            return true;
        if (*b1 < *b2)
            return false;
        b1++;
        b2++;
    }
    return false;
}