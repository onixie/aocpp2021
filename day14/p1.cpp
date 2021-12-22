#include "lib.hpp"
#include <algorithm>
#include <iostream>

int main() {
    PolyTemplate poly;
    std::cin>>poly;
    std::cerr<<poly<<std::endl;

    InsertRules rules;
    std::cin>>rules;
    std::cerr<<rules;

    for(int i=0; i < PROCESS; i++) {
        process1(poly, rules);
        std::cerr<<poly<<" ("<<poly.size()+1<<")"<<std::endl;
    }

    auto cnts = count(poly);
    auto max = std::max_element(cnts.begin(), cnts.end(), [](auto c1, auto c2) {
        return std::get<1>(c1) < std::get<1>(c2);
    });
    auto min = std::min_element(cnts.begin(), cnts.end(), [](auto c1, auto c2) {
        return std::get<1>(c1) < std::get<1>(c2);
    });

    std::cerr<<(*max).first<<", "<<(*max).second<<std::endl;
    std::cerr<<(*min).first<<", "<<(*min).second<<std::endl;

    std::cout<<(*max).second - (*min).second<<std::endl;
    return 0;
}