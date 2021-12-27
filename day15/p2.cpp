#include "lib.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <queue>
#include <vector>

inline Chiton inc(Chiton const& c, int i, int x, int y, int width, int height) {
    auto nc = c;
    nc.risk = (c.risk+i)%9;
    if (nc.risk == 0) nc.risk = 9;
    nc.x = c.x + x * width;
    nc.y = c.y + y * height;
    return nc;
}

void extend_map(Cavern& cave) {
    for(auto&row : cave.chitons) {
        std::vector<Chiton> tmp;
        for(int i = 0; i< 5; i++) {
            std::for_each(row.cbegin(), row.cend(), [&tmp, &row, i](auto& c) { tmp.emplace_back(inc(c, i, i, 0, row.size(), 0)); });
        }
        row.swap(tmp);
    }

    std::vector<std::vector<Chiton>> tmpc;
    for(int i = 0; i< 5; i++) {
        for(auto&row : cave.chitons) {
            std::vector<Chiton> tmp;
            std::for_each(row.cbegin(), row.cend(), [&tmp, &cave, i](auto& c) { tmp.emplace_back(inc(c, i, 0, i, 0, cave.chitons.size())); });
            tmpc.emplace_back(tmp);
        }
    }
    cave.chitons.swap(tmpc);

    cave.width *= 5;
    cave.height*= 5;
}


int main() {
    Cavern cave;
    std::cin>>cave;

    extend_map(cave);
    //std::cerr<<cave;
    
    cave.chitons[0][0].total_risk = 0;
    MinChitons mins; mins.push_back(&cave.chitons[0][0]);

    int risk = -1;
    while((risk=dijkstra(cave, mins))==-1) {
        //std::cerr<<cave;
        //sleep(1);
        //std::cerr<<std::endl;
    }
    std::cerr<<cave;
    std::cout<<risk<<std::endl;
    return 0;
}