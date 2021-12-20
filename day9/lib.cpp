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
        for(auto& cell: row) {
            out<<static_cast<int>(cell)<<"("<<cell.tag<<")"<<" ";
        }
        out<<std::endl;
    }
    return out;
}

Loc up(int col, int row, HeightMap const& map) {
    if (row - 1 < 0)
        return {std::numeric_limits<char>::max()};
    return map.data[row-1][col];
}

Loc down(int col, int row, HeightMap const& map) {
    if (row + 1 >= map.height)
        return {std::numeric_limits<char>::max()};
    return map.data[row+1][col];
}

Loc left(int col, int row, HeightMap const& map) {
    if (col - 1 < 0)
        return {std::numeric_limits<char>::max()};
    return map.data[row][col - 1];
}

Loc right(int col, int row, HeightMap const& map) {
    if (col + 1 >= map.width)
        return {std::numeric_limits<char>::max()};
    return map.data[row][col + 1];
}

int visit(int col, int row, HeightMap& map, int tag) {
    if (col < 0 || col >= map.width || row < 0 || row >= map.height)
        return tag;
        
    if (map.data[row][col].tag == 0 && map.data[row][col] < 9) {
        map.data[row][col].tag = tag;
        visit(col+1, row, map, tag);
        visit(col-1, row, map, tag);
        visit(col, row+1, map, tag);
        visit(col, row-1, map, tag);
        return tag+1;
    }

    return tag;
}

int visit_all(HeightMap& map) {
    int tag = 1;
    for(int row = 0; row < map.height; row++) {
        for (int col = 0; col < map.width; col++) {
            tag = visit(col, row, map, tag);
        }
    }
    return tag;
}