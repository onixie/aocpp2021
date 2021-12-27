#include "lib.hpp"
#include <cstddef>
#include <limits>
#include <tuple>
#include <unistd.h>
#include <vector>


int main() {
    Cavern cave;
    
    std::cin>>cave;
    
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