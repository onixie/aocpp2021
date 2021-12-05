#ifndef _LIB_H_
#define _LIB_H_

#include <unordered_map>
#include <tuple>
#include <vector>
#include <iostream>
#include <array>

struct Boards {
    std::vector<std::array<std::array<std::tuple</*num*/uint,/*marker*/bool>, 5>,5>> list;  //list of 5x5 boards
    std::unordered_map<uint, std::vector<std::tuple</*board index*/uint, /*col index*/uint, /*row index*/uint>>> lookupTable;

    uint score(std::tuple</*board index*/uint, /* number */uint> const& res) const{
        auto board = this->list[std::get<0>(res)];
        auto num = std::get<1>(res);
        auto sum = 0;
        for(auto& row : board)
            for(auto& cell : row) {
                if (!std::get<1>(cell))
                    sum+=std::get<0>(cell);
            }
        return num*sum;
    }
};

struct Numbers {
    std::vector<uint> list;
};

extern std::ostream& operator<<(std::ostream& out, Numbers const& numbers);
extern std::ostream& operator<<(std::ostream& out, Boards const& boards);
extern std::istream& operator>>(std::istream& in, Numbers& numbers);
extern std::istream& operator>>(std::istream& in, Boards& boards);

#endif // _LIB_H_