#include "lib.hpp"

std::istream& operator>>(std::istream& in, HeightMap& map) {
    do {
        char c; in.get(c);

        if (in.eof()) {
            map.height += 1;
            return in;
        }

        if (c == '\n' || c == '\r') {
            map.width = map.data[map.height].size();
            map.height += 1;
            map.data.emplace_back();
            continue;
        }

        map.data[map.height].push_back(c - '0');
    } while (true);
    return in;
}

std::ostream& operator<<(std::ostream& out, HeightMap const& map) {
    for(auto& row: map.data) {
        for(auto cell: row) {
            out<<static_cast<int>(cell)<<" ";
        }
        out<<std::endl;
    }
    return out;
}


int up(int col, int row, HeightMap const& map) {
    if (row - 1 < 0)
        return std::numeric_limits<int>::max();
    return static_cast<int>(map.data[row-1][col]);
}

int down(int col, int row, HeightMap const& map) {
    if (row + 1 >= map.height)
        return std::numeric_limits<int>::max();
    return static_cast<int>(map.data[row+1][col]);
}

int left(int col, int row, HeightMap const& map) {
    if (col - 1 < 0)
        return std::numeric_limits<int>::max();
    return static_cast<int>(map.data[row][col - 1]);
}

int right(int col, int row, HeightMap const& map) {
    if (col + 1 >= map.width)
        return std::numeric_limits<int>::max();
    return static_cast<int>(map.data[row][col + 1]);
}