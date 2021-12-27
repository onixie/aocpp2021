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
            //<<"("<<cell.x<<","<<cell.y<<")"
            //<<"("<<(cell.visited ? ("*") : " ")<<","<<(cell.visited ? cell.total_risk : 0)<<")"
            <<"";
        }
        out<<std::endl;
    }
    return out;
}

static constexpr bool greator(Chiton const* c1, Chiton const* c2) {
    return c1->total_risk > c2->total_risk;
}

void MinChitons::push_back(Chiton* cp) {
    if (!std::is_heap(std::begin(*this), std::end(*this))) {
        std::make_heap(std::begin(*this), std::end(*this), greator);
    }

    std::vector<Chiton*>::push_back(cp);
    std::push_heap(std::begin(*this), std::end(*this), greator);
}

void MinChitons::pop_back() {
    std::pop_heap(std::begin(*this), std::end(*this), greator);
    std::vector<Chiton*>::pop_back();
}

void MinChitons::rebalance() {
    std::make_heap(std::begin(*this), std::end(*this), greator);
}

static constexpr bool can_move(Cavern const& cave, int x, int y) {
    if (x < 0 || x >= cave.width || y < 0 || y >= cave.height || cave.chitons[y][x].visited)
        return false;
    return true;
}

static constexpr bool reach_goal(Cavern const& cave, int x, int y) {
    return x == cave.width - 1 && y == cave.height - 1;
}

int dijkstra(Cavern& cave, MinChitons& mins) {
    const static std::array<std::array<int, 2>, 4> moves = {{
        {0, -1}, 
        {0,  1}, 
        {-1, 0}, 
        {1,  0},
    }};

    // get min total risk chiton found so far
    auto& min = *mins.front();
    min.visited = true;
    mins.pop_back();

    // if reach goal, return total risk
    if (reach_goal(cave, min.x, min.y))
        return min.total_risk;

    // find adjacent chitons and recalculate total risks
    for(auto& m: moves) {
        int ax = min.x + m[0];
        int ay = min.y + m[1];

        if (can_move(cave, ax, ay)) {
            auto old_total_risk = cave.chitons[ay][ax].total_risk;
            auto new_total_risk = cave.chitons[ay][ax].risk + min.total_risk;

            if (old_total_risk == std::numeric_limits<size_t>::max()) { // never passed-by
                cave.chitons[ay][ax].total_risk = new_total_risk;
                mins.push_back(&cave.chitons[ay][ax]);
            } else if (old_total_risk > new_total_risk) { // had passed-by at least once and need to update min total risk
                cave.chitons[ay][ax].total_risk = new_total_risk;
                mins.rebalance();
            }
        }
    }

    return -1; // goal not yet reached
}