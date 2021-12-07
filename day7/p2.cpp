#include "lib.hpp"
#include <algorithm>

int main(int argc, char** argv) {
    Submarines submarines;
    std::cin>>submarines;
    std::cerr<<submarines<<std::endl;

    size_t least_cost = -1;
    size_t least_pos = -1;
    size_t maxpos = *std::max_element(submarines.cbegin(), submarines.cend());
    for(int pos = 0; pos <= maxpos; pos++) {
        size_t sum = 0;
        for (auto crab1: submarines) {
            int dist = std::abs(crab1 - pos);
            sum += (1+dist)*dist/2;
        }
        
        if (least_cost > sum) {
            least_cost = sum;
            least_pos = pos;
        }

        // std::cerr<<crab1<<std::endl;
        // std::cout<<sum<<std::endl;
    }

    std::cerr<<least_pos<<std::endl;
    std::cout<<least_cost<<std::endl;
    return 0;
}