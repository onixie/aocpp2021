#include "lib.hpp"

int main() {
    Line chunks;
    int pts = 0;
    do {
        std::cin>>chunks;
        if (chunks.invalid != std::nullopt) {
            pts += SCORE.at(std::get<1>(*chunks.invalid));
        }
        std::cerr<<chunks<<std::endl;
        chunks.clear();
    } while (!std::cin.eof());

    std::cout<<pts<<std::endl;
    return 0;
}