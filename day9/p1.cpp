#include "lib.hpp"

int main() {
    HeightMap map;
    std::cin>>map;
    std::cerr<<map<<std::endl;
    
    int s = 0;
    for(int row = 0; row < map.height; row++) {
        for (int col = 0; col < map.width; col++) {
            int c = map.data[row][col];
            int u = up(col, row, map);
            int d = down(col, row, map);
            int r = right(col, row, map);
            int l = left(col, row, map);
           
            if (c < u && c < d && c < l && c < r) {
                s+=c+1;
            }
        }
    }
    std::cout<<s<<std::endl;
    return 0;
}

