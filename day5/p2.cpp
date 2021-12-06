#include "lib.hpp"
#include <vector>
#include <tuple>

void draw(Diagram& diagram, Vents const& vents);

int main() {
    Vents vents;
    std::cin>>vents;
    std::cerr<<vents;
    Diagram diagram(vents);
    //std::cerr<<diagram;
    
    draw(diagram, vents);
    std::cerr<<diagram;
    std::cout<<diagram.count_cross()<<std::endl;
    
    return 0;
}

void draw(Diagram& diagram, Vents const& vents) {
    for(auto& line : vents.lines) {
        if (line.start.x == line.end.x) {
            uint miny = std::min(line.start.y,line.end.y);
            uint maxy = std::max(line.start.y,line.end.y);

            for(;miny<=maxy;miny++) {
                diagram.get(line.start.x, miny)++;
            }
        }
        else if (line.start.y == line.end.y) {
            uint minx = std::min(line.start.x, line.end.x);
            uint maxx = std::max(line.start.x, line.end.x);

            for(;minx<=maxx;minx++) {
                diagram.get(minx, line.start.y)++;
            }
        } 
        else if (std::abs(int(line.start.x) - int(line.end.x)) == std::abs(int(line.start.y) - int(line.end.y))) {
            
            int p = std::abs(int(line.start.x) - int(line.end.x));
            uint sx = line.start.x;
            uint sy = line.start.y;

            for(; p >= 0; p--) {
                diagram.get(sx, sy)++;

                if (sx <= line.end.x)
                    sx++;
                else
                    sx--;

                if (sy <= line.end.y)
                    sy++;
                else
                    sy--;
            }
        }
    }
}