#include "lib.hpp"
#include <array>

std::istream& operator>>(std::istream& in, Cavern& map) {
    do {
        char c; in.get(c);

        if (in.eof()) {
            map.height += 1;
            return in;
        }

        if (c == '\n' || c == '\r') {
            map.width = map.chitons[map.height].size();
            map.height += 1;
            map.chitons.emplace_back();
            continue;
        }

        map.chitons[map.height].emplace_back(c - '0', map.chitons[map.height].size(), map.height);
    } while (true);
    return in;
}

std::ostream& operator<<(std::ostream& out, Cavern const& map) {
    for(auto& row: map.chitons) {
        for(auto& cell: row) {
            out<<static_cast<int>(cell.risk)
            <<"("<<cell.x<<","<<cell.y<<")"
            //<<"("<<(cell.visited ? ("*") : " ")<<","<<(cell.visited ? cell.total_risk : 0)<<")"
            <<" ";
        }
        out<<std::endl;
    }
    return out;
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
            } else if (cave.chitons[ay][ax].total_risk > new_total_risk)
                cave.chitons[ay][ax].total_risk = new_total_risk;
            //std::cerr<<ax<<" "<<ay<<" "<<cave.chitons[ay][ax].total_risk<<std::endl;
        }
    }

    return -1;
}