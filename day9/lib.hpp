#ifndef _LIB_H_
#define _LIB_H_
#include <limits>
#include <vector>
#include <iostream>

struct Loc {
    Loc(char c): c(c), tag(0) {}
    char c;
    int tag;
    operator int() const {
        return static_cast<int>(c);
    }
};

struct HeightMap {
    std::vector<std::vector<Loc>> data = {{}};
    size_t width = 0;
    size_t height = 0;

    int basin_size(int tag) {
        int size = 0;
        for(auto& row: data) {
            for(auto& cell: row) {
                if (cell.tag == tag)
                    size++;
            }
        }
        return size;
    }
};

using dir = Loc(int col, int row, HeightMap const& map);

dir up;
dir down;
dir left;
dir right;

int visit(int col, int row, HeightMap& map);
int visit_all(HeightMap& map);

std::istream& operator>>(std::istream&, HeightMap&);
std::ostream& operator<<(std::ostream&, HeightMap const&);

#endif //_LIB_H_