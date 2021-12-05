#include "lib.hpp"
#include <vector>
#include <tuple>

std::tuple<uint/*max*/,uint/*count*/> draw(Diagram& diagram, Vents const& vents);

int main() {
    Vents vents;
    std::cin>>vents;
    std::cerr<<vents;
    Diagram diagram(vents);
    //std::cerr<<diagram;
    
    std::tuple<uint, uint> res = draw(diagram, vents);
    std::cerr<<std::get<0>(res)<<", "<<diagram.count(std::get<0>(res))<<std::endl;
    
    //std::cerr<<diagram;
    return 0;
}

std::tuple<uint/*max*/,uint/*count*/> draw(Diagram& diagram, Vents const& vents) {
    uint max = 0;
    uint cnt = 0;
    for(auto& line : vents.lines) {
        if (line.start.x == line.end.x) {
            uint miny = std::min(line.start.y,line.end.y);
            uint maxy = std::max(line.start.y,line.end.y);

            for(;miny<=maxy;miny++) {
                uint c = ++diagram.get(line.start.x, miny);
                
                if (c>1)
                    cnt++;

                std::cerr<<line.start.x<<","<<miny<<","<<max<<","<<cnt<<std::endl;

                max = std::max(max, diagram.get(line.start.x, miny));
            }
        }
        else if (line.start.y == line.end.y) {
            uint minx = std::min(line.start.x, line.end.x);
            uint maxx = std::max(line.start.x, line.end.x);

            for(;minx<=maxx;minx++) {
                uint c = ++diagram.get(minx, line.start.y);
                
                if (c>1)
                    cnt++;
                
                std::cerr<<minx<<","<<line.start.y<<","<<max<<","<<cnt<<std::endl;
                max = std::max(max, diagram.get(minx, line.start.y));
            }
        }
    }
    return {max, cnt};
}