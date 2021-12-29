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
        std::cerr<<ver(bits, index)<<" "<<ver.value<<std::endl;
        std::cerr<<typ(bits, index)<<" "<<typ.value<<std::endl;
        std::cerr<<lit(bits, index)<<" "<<lit.value<<std::endl;
        std::cerr<<lit(bits, index)<<" "<<lit.value<<std::endl;
        std::cerr<<lit(bits, index)<<" "<<lit.value<<std::endl;
    }
    {
        size_t index = 0;
        BITSLvPac lv;lv(bits, index);
        std::cerr<<lv<<std::endl;
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
        std::cerr<<ver(bits, index)<<" "<<std::dec<<ver.value<<std::endl;
        std::cerr<<typ(bits, index)<<" "<<std::dec<<typ.value<<std::endl;
        std::cerr<<mod(bits, index)<<" "<<std::dec<<mod.value<<std::endl;
        std::cerr<<len(bits, index)<<" "<<std::dec<<len.value<<std::endl;
        {
            BITSVer ver;
            BITSTyp typ;
            BITSLit lit;
            std::cerr<<ver(bits, index)<<" "<<ver.value<<std::endl;
            std::cerr<<typ(bits, index)<<" "<<typ.value<<std::endl;
            std::cerr<<lit(bits, index)<<" "<<lit.value<<std::endl;
        }
        {
            BITSVer ver;
            BITSTyp typ;
            BITSLit lit;
            std::cerr<<ver(bits, index)<<" "<<ver.value<<std::endl;
            std::cerr<<typ(bits, index)<<" "<<typ.value<<std::endl;
            std::cerr<<lit(bits, index)<<" "<<lit.value<<std::endl;
            std::cerr<<lit(bits, index)<<" "<<lit.value<<std::endl;
        }
    }
    {
        
        size_t index = 0;
        BITSOpPac op;op(bits, index);
        std::cerr<<op<<std::endl;
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
        std::cerr<<ver(bits, index)<<" "<<std::dec<<ver.value<<std::endl;
        std::cerr<<typ(bits, index)<<" "<<std::dec<<typ.value<<std::endl;
        std::cerr<<mod(bits, index)<<" "<<std::dec<<mod.value<<std::endl;
        std::cerr<<len(bits, index)<<" "<<std::dec<<len.value<<std::endl;
        {
            BITSVer ver;
            BITSTyp typ;
            BITSLit lit;
            std::cerr<<ver(bits, index)<<" "<<ver.value<<std::endl;
            std::cerr<<typ(bits, index)<<" "<<typ.value<<std::endl;
            std::cerr<<lit(bits, index)<<" "<<lit.value<<std::endl;
        }
        {
            BITSVer ver;
            BITSTyp typ;
            BITSLit lit;
            std::cerr<<ver(bits, index)<<" "<<ver.value<<std::endl;
            std::cerr<<typ(bits, index)<<" "<<typ.value<<std::endl;
            std::cerr<<lit(bits, index)<<" "<<lit.value<<std::endl;
        }
        {
            BITSVer ver;
            BITSTyp typ;
            BITSLit lit;
            std::cerr<<ver(bits, index)<<" "<<ver.value<<std::endl;
            std::cerr<<typ(bits, index)<<" "<<typ.value<<std::endl;
            std::cerr<<lit(bits, index)<<" "<<lit.value<<std::endl;
        }
    }
    {
        size_t index = 0;
        BITSOpPac op; op(bits, index);
        std::cerr<<op<<std::endl;
    }
    return 0;
}

