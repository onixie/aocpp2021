#include "lib.hpp"

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
            out<<static_cast<int>(cell.risk)<<"("<<(cell.visited ? ("*") : " ")<<","<<(cell.visited ? cell.total_risk : 0)<<")"<<" ";
        }
        out<<std::endl;
    }
    return out;
}