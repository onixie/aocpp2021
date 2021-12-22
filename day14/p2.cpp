#include "lib.hpp"
#include <algorithm>
#include <iostream>

int main() {
    PolyTemplate polyt;
    std::cin>>polyt;
    std::cerr<<polyt<<std::endl;

    InsertRules rules;
    std::cin>>rules;
    std::cerr<<rules;

    PolyCounts polyc;
    Counts cnts;
    init_counts(polyt, polyc, cnts);
    std::cerr<<polyc;

    for(int i=0; i < PROCESS; i++) {
        //process1(polyt, rules); // test only
        //std::cerr<<polyt<<std::endl;

        process1_opt(polyc, cnts, rules);
        std::cerr<<polyc;
    }

    // final result:
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