#ifndef _LIB_H_
#define _LIB_H_

#include <unordered_map>
#include <tuple>
#include <vector>
#include <iostream>

struct Boards {
    using BoardIndex = uint;
    using Col = uint;
    using Row = uint;
    std::unordered_map<uint, std::tuple<BoardIndex, Col, Row>> lookupTable;
};

struct Numbers {
    std::vector<uint> list;
};

extern std::ostream& operator<<(std::ostream& out, Numbers const& numbers);
extern std::ostream& operator<<(std::ostream& out, Boards const& boards);
extern std::istream& operator>>(std::istream& in, Numbers& numbers);
extern std::istream& operator>>(std::istream& in, Boards& boards);

#endif // _LIB_H_