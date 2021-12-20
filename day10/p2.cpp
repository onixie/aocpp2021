#include "lib.hpp"

const std::unordered_map<char, int> SCORE = {
    {'>', 4},
    {'}', 3},
    {']', 2},
    {')', 1},
};

int main() {
    Line chunks;
    std::vector<std::int64_t> pts = {};
    do {
        std::cin>>chunks;
        std::cerr<<chunks<<std::endl;

        if (chunks.invalid == std::nullopt) {
            pts.emplace_back(0);
            for(auto& c: chunks.ac()) {
                pts.back() = pts.back()*5 + SCORE.at(c);
            }
        }

        chunks.clear();
    } while (!std::cin.eof());

    std::sort(pts.begin(), pts.end());
    for(auto pt: pts)
        std::cerr<<pt<<std::endl;
    
    std::cout<<pts[pts.size()/2]<<std::endl;
    return 0;
}