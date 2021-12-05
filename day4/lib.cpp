#include "lib.hpp"
#include <sstream>
#include <string>
#include <algorithm>

std::ostream& operator<<(std::ostream& out, Numbers const& numbers) {
    std::stringstream ss;
    for (auto iter = numbers.list.cbegin(); iter < numbers.list.cend(); iter++) {
        ss<<*iter;
        if (std::distance(iter, numbers.list.cend()) > 1)
            ss<<",";
    }
    out<<ss.str()<<std::endl;
    return out;
}

std::ostream& operator<<(std::ostream& out, Boards const& boards) {
    std::for_each(boards.list.cbegin(), boards.list.cend(), [&out](auto board){
        std::for_each(board.cbegin(), board.cend(), [&out](auto row) {
            std::for_each(row.cbegin(), row.cend(), [&out](auto cell){
                if (std::get<1>(cell))
                    out<<"+";
                else
                    out<<"";
                out<<std::get<0>(cell)<<" ";
            });
            out<<std::endl;
        });
        out<<std::endl;
    });

    #ifdef DEBUG
    for(auto const& lookup : boards.lookupTable) {
        std::cerr<<lookup.first<<": ";
        for(auto const& loc : lookup.second) {
            std::cerr<<"("<<std::get<0>(loc)<<","<<std::get<1>(loc)<<","<<std::get<2>(loc)<<") ";
        }
        std::cerr<<std::endl;
    };
    #endif

    return out;
};

std::istream& operator>>(std::istream& in, Numbers& numbers) {
    std::string tmp;
    getline(in, tmp);
    std::stringstream ss;
    ss<<tmp;
    while(getline(ss, tmp, ','))
        numbers.list.emplace_back(std::stoi(tmp));
    return in;
}
std::istream& operator>>(std::istream& in, Boards& boards) {
    do {
        std::array<std::array<std::tuple<uint, bool>, 5>, 5> board;
        for (uint r = 0; r<5; r++) {
            std::array<std::tuple<uint, bool>, 5> row;
            for (uint c = 0; c<5; c++) {
                uint v = 0;
                in>>v;

                std::get<0>(board[r][c])=v;
                std::get<1>(board[r][c])=false;

                boards.lookupTable[v].emplace_back(boards.list.size(), r, c);
            }
        }
        boards.list.emplace_back(board);
    } while (!in.eof());

    return in;
}