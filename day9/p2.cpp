#include "lib.hpp"
#include <queue>

int main() {
    HeightMap map;
    std::cin>>map;
    
    int tag = visit_all(map);
    std::cerr<<map<<std::endl;

    std::priority_queue<int> bs = {};
    while(tag-- > 1) {
        std::cerr<<tag<<" "<<map.basin_size(tag)<<std::endl;
        bs.push(map.basin_size(tag));
    }

    int bs1 = bs.top(); bs.pop();
    int bs2 = bs.top(); bs.pop();
    int bs3 = bs.top();

    std::cout<<bs1*bs2*bs3<<std::endl;
    return 0;
}