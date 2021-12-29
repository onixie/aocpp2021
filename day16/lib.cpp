#include "lib.hpp"
#include <cstdint>
#include <ios>
#include <bitset>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <iomanip>


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

std::string BITSLvPac::operator()(BITStream const& stream, size_t& index) {
    size_t idx=index;

    bits+=ver(stream, idx).to_string();
    bits+=typ(stream, idx).to_string();

    if (typ.value == 4) {
        BITSLit lit;
        do {
            auto l = lit(stream, idx);
            bits+=l.to_string();
            value = (value<<4) + (0x0F&lit.value);
            if (!l.test(4))
                break;
        } while (true);

        index = idx;
        pack = Lv;
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
    out<<"value: "<<std::dec<<pac.value<<std::endl;
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