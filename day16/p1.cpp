#include "lib.hpp"
#include <cstdint>
#include <iostream>
#include <ostream>

int main() {

    BITStream bits;

    std::cin>>bits;
    std::cerr<<bits<<std::endl;
    {
        BITSVer ver;
        BITSTyp typ;
        BITSLit lit;
        size_t index = 0;
        std::cerr<<ver.parse(bits, index)<<" "<<ver.value<<std::endl;
        std::cerr<<typ.parse(bits, index)<<" "<<typ.value<<std::endl;
        std::cerr<<lit.parse(bits, index)<<" "<<lit.value<<std::endl;
        std::cerr<<lit.parse(bits, index)<<" "<<lit.value<<std::endl;
        std::cerr<<lit.parse(bits, index)<<" "<<lit.value<<std::endl;
    }
    bits.clear();
    std::cin>>bits;
    std::cerr<<bits<<std::endl;
    {
        BITSVer ver;
        BITSTyp typ;
        BITSLit lit;
        BITSMod mod;
        BITS<std::uint32_t, 15> len;
        size_t index = 0;
        std::cerr<<ver.parse(bits, index)<<" "<<std::dec<<ver.value<<std::endl;
        std::cerr<<typ.parse(bits, index)<<" "<<std::dec<<typ.value<<std::endl;
        std::cerr<<mod.parse(bits, index)<<" "<<std::dec<<mod.value<<std::endl;
        std::cerr<<len.parse(bits, index)<<" "<<std::dec<<len.value<<std::endl;
        {
            BITSVer ver;
            BITSTyp typ;
            BITSLit lit;
            std::cerr<<ver.parse(bits, index)<<" "<<ver.value<<std::endl;
            std::cerr<<typ.parse(bits, index)<<" "<<typ.value<<std::endl;
            std::cerr<<lit.parse(bits, index)<<" "<<lit.value<<std::endl;
        }
        {
            BITSVer ver;
            BITSTyp typ;
            BITSLit lit;
            std::cerr<<ver.parse(bits, index)<<" "<<ver.value<<std::endl;
            std::cerr<<typ.parse(bits, index)<<" "<<typ.value<<std::endl;
            std::cerr<<lit.parse(bits, index)<<" "<<lit.value<<std::endl;
            std::cerr<<lit.parse(bits, index)<<" "<<lit.value<<std::endl;
        }
    }

    bits.clear();
    std::cin>>bits;
    std::cerr<<bits<<std::endl;
    {
        BITSVer ver;
        BITSTyp typ;
        BITSLit lit;
        BITSMod mod;
        BITS<std::uint32_t, 11> len;
        size_t index = 0;
        std::cerr<<ver.parse(bits, index)<<" "<<std::dec<<ver.value<<std::endl;
        std::cerr<<typ.parse(bits, index)<<" "<<std::dec<<typ.value<<std::endl;
        std::cerr<<mod.parse(bits, index)<<" "<<std::dec<<mod.value<<std::endl;
        std::cerr<<len.parse(bits, index)<<" "<<std::dec<<len.value<<std::endl;
        {
            BITSVer ver;
            BITSTyp typ;
            BITSLit lit;
            std::cerr<<ver.parse(bits, index)<<" "<<ver.value<<std::endl;
            std::cerr<<typ.parse(bits, index)<<" "<<typ.value<<std::endl;
            std::cerr<<lit.parse(bits, index)<<" "<<lit.value<<std::endl;
        }
        {
            BITSVer ver;
            BITSTyp typ;
            BITSLit lit;
            std::cerr<<ver.parse(bits, index)<<" "<<ver.value<<std::endl;
            std::cerr<<typ.parse(bits, index)<<" "<<typ.value<<std::endl;
            std::cerr<<lit.parse(bits, index)<<" "<<lit.value<<std::endl;
        }
        {
            BITSVer ver;
            BITSTyp typ;
            BITSLit lit;
            std::cerr<<ver.parse(bits, index)<<" "<<ver.value<<std::endl;
            std::cerr<<typ.parse(bits, index)<<" "<<typ.value<<std::endl;
            std::cerr<<lit.parse(bits, index)<<" "<<lit.value<<std::endl;
        }
    }
    return 0;
}

