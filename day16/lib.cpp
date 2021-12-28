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
        in>>lb>>hb;
        if (in.eof())
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