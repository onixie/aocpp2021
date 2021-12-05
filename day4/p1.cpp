#include "lib.hpp"

std::tuple<uint, uint> play_bingo(Numbers const& numbers, Boards& boards);

int main() {
    Numbers numbers;
    Boards boards;

    std::cin>>numbers;
    std::cerr<<numbers;

    std::cerr<<std::endl;
    
    std::cin>>boards;
    std::cerr<<boards;
    
    auto res = play_bingo(numbers, boards);

    std::cerr<<"-----"<<std::endl;
    std::cerr<<boards;

    std::cout<<boards.score(res)<<std::endl;
    return 0;
}

std::tuple<uint, uint> play_bingo(Numbers const& numbers, Boards& boards) {
    std::vector<std::array<uint, 5>> col_mark_counters(boards.list.size(), {0,0,0,0,0});
    std::vector<std::array<uint, 5>> row_mark_counters(boards.list.size(), {0,0,0,0,0});

    for(auto n: numbers.list){
        auto locs = boards.lookupTable.find(n);
        if (locs != boards.lookupTable.end())
            for(auto loc: locs->second) {
                uint b = std::get<0>(loc);
                uint r = std::get<1>(loc);
                uint c = std::get<2>(loc);

                std::get<1>(boards.list[b][r][c]) = true;

                row_mark_counters[b][r]++;
                col_mark_counters[b][c]++;

                if (row_mark_counters[b][r] >= 5 || col_mark_counters[b][c] >= 5)
                    return {b, n};
            }
    }
}