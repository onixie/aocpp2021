#include "lib.hpp"
#include <algorithm>

int main(int argc, char** argv) {
    Submarines submarines;
    std::cin>>submarines;
    std::cerr<<submarines<<std::endl;

    size_t least_cost = -1;
    size_t least_crab = -1;
    for(auto crab1: submarines) {
        size_t sum = 0;
        for (auto crab2: submarines) {
            sum+=std::abs(crab1 - crab2);
        }
        
        if (least_cost > sum) {
            least_cost = sum;
            least_crab = crab1;
        }
    }

    std::cerr<<least_crab<<std::endl;
    std::cout<<least_cost<<std::endl;
    return 0;
}