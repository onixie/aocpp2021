#include "lib.hpp"
#include <cstdint>
#include <ios>
#include <bitset>
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
        out<<std::setw(2)<<std::setfill('0')<<std::hex<<(0xFFUL&hex);
    }
    out<<", bin: ";
    for(auto dec: stream) {
        out<<std::dec<<(0xFUL&dec>>4)<<", ";
        out<<std::dec<<(0xFUL&dec)<<", ";
    }
    return out;
}