#include "lib.hpp"
#include <algorithm>

int main() {
    Map map;

    std::cin>>map;
    std::cerr<<map;

    map.traverse(true);
    auto tracks_cnt = map.print_tracks(std::cerr);
    
    std::cout<<tracks_cnt<<std::endl;
    return 0;
}