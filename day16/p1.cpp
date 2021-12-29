#include "lib.hpp"
#include <cstdint>
#include <iostream>
#include <ostream>

int sum_version(BITSPacBase* p);

int main() {

    BITStream bits;
    std::cin>>bits;
    std::cerr<<bits<<std::endl;

    size_t index = 0;
    auto p = parse(bits, index); print(p);
    
    std::cout<<sum_version(p.get())<<std::endl;
    return 0;
}

int sum_version(BITSPacBase* p) {
    if (p->pack == BITSPacBase::Op) {
        int ret = p->ver.value;
        for(auto& sp: static_cast<BITSOpPac*>(p)->subpacs) {
            ret += sum_version(sp.get());
        }
        return ret;
    }
    return p->ver.value;
}