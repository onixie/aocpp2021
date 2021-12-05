#include "lib.hpp"
#include <vector>

int main() {
    Vents vents;
    std::cin>>vents;

    for(auto& line: vents.lines) {
        std::cerr<<line<<std::endl;
    }
    std::cerr<<vents<<std::endl;

    return 0;
}