#ifndef _LIB_H_
#define _LIB_H_
#include <limits>
#include <array>
#include <iostream>

struct Oct {
    Oct(): c(-1), flashed(false) {}
    Oct(char c): c(c), flashed(false) {}
    char c;
    bool flashed;
    operator int() const {
        return static_cast<int>(c);
    }
};

struct Cavern {
    std::array<std::array<Oct, 10>, 10> octs;
};

using dir = Oct(int col, int row, Cavern const& map);

dir up;
dir down;
dir left;
dir right;

int visit_all(Cavern& map);
int step1(Cavern& cave);

std::istream& operator>>(std::istream&, Cavern&);
std::ostream& operator<<(std::ostream&, Cavern const&);

#endif //_LIB_H_