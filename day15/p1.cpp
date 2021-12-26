#include "lib.hpp"
#include <cstddef>
#include <limits>
#include <tuple>
#include <unistd.h>
#include <vector>
#include <array>

int dijkstra(Cavern& cave, MinChiton& mins);

int main() {
    Cavern cave;
    
    std::cin>>cave;
    std::cerr<<cave;
    
    cave.chitons[0][0].total_risk = 0;
    MinChiton mins; mins.push(&cave.chitons[0][0]);

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

inline bool can_move(Cavern& cave, int x, int y) {
    if (x < 0 || x >= cave.width || y < 0 || y >= cave.height || cave.chitons[y][x].visited)
        return false;
    return true;
}

inline bool reach_goal(Cavern& cave, int x, int y) {
    return x == cave.width - 1 && y == cave.height - 1;
}

const std::array<std::array<int, 2>, 4> moves = {{{0, -1}, {0, 1}, {-1, 0}, {1, 0}, }};

int dijkstra(Cavern& cave, MinChiton& mins) {
    auto& min = *mins.top();
    min.visited = true;
    mins.pop();

    if (reach_goal(cave, min.x, min.y))
        return min.total_risk;

    for(auto& m: moves) {
        int ax = min.x + m[0];
        int ay = min.y + m[1];
        if (can_move(cave, ax, ay)) {
            auto old_total_risk = cave.chitons[ay][ax].total_risk;
            auto new_total_risk = cave.chitons[ay][ax].risk + min.total_risk;

            if (old_total_risk == std::numeric_limits<size_t>::max()) {
                cave.chitons[ay][ax].total_risk = new_total_risk;
                mins.push(&cave.chitons[ay][ax]);
            } else  if (cave.chitons[ay][ax].total_risk > new_total_risk)
                cave.chitons[ay][ax].total_risk = new_total_risk;
            //std::cerr<<ax<<" "<<ay<<" "<<cave.chitons[ay][ax].total_risk<<std::endl;
        }
    }

    return -1;
}