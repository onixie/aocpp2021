#include "lib.hpp"
#include <cstdint>
#include <iostream>
#include <ostream>

int main() {

    BITStream bits;

    std::cin>>bits;
    std::cerr<<bits<<std::endl;
    std::cerr<<(bits<<1)<<std::endl;
    std::cerr<<(bits<<2)<<std::endl;
    std::cerr<<(bits<<3)<<std::endl;
    std::cerr<<(bits<<4)<<std::endl;
    std::cerr<<(bits<<5)<<std::endl;
    std::cerr<<(bits<<6)<<std::endl;
    std::cerr<<(bits<<7)<<std::endl;
    std::cerr<<(bits<<8)<<std::endl;
    std::cerr<<(bits<<9)<<std::endl;
    std::cerr<<(bits<<10)<<std::endl;
    std::cerr<<(bits<<11)<<std::endl;

    BITSVer ver;
    BITSTyp typ;
    BITSLit lit;
    size_t index = 0;
    std::cerr<<ver.parse(bits, index)<<" "<<ver.value<<std::endl;
    std::cerr<<typ.parse(bits, index)<<" "<<typ.value<<std::endl;
    std::cerr<<lit.parse(bits, index)<<" "<<lit.value<<std::endl;
    std::cerr<<lit.parse(bits, index)<<" "<<lit.value<<std::endl;
    std::cerr<<lit.parse(bits, index)<<" "<<lit.value<<std::endl;

    index = 0;
    std::cerr<<typ.parse(bits<<3, index)<<" "<<typ.value<<std::endl;

    index = 0;
    std::cerr<<lit.parse(bits<<11, index)<<" "<<lit.value<<std::endl;

    index = 0;
    std::cerr<<lit.parse(bits<<16, index)<<" "<<lit.value<<std::endl;
    return 0;
}

