#ifndef _LIB_H_
#define _LIB_H_
#include <limits>
#include <vector>
#include <iostream>

struct HeightMap {
    std::vector<std::vector<char>> data = {{}};
    size_t width = 0;
    size_t height = 0;
};

using dir = int(int col, int row, HeightMap const& map);

dir up;
dir down;
dir left;
dir right;

std::istream& operator>>(std::istream&, HeightMap&);
std::ostream& operator<<(std::ostream&, HeightMap const&);

#endif //_LIB_H_