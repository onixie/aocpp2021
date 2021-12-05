#include "lib.hpp"
#include <algorithm>

std::ostream& operator<<(std::ostream& out, Point const& point) {
    out<<point.x<<","<<point.y;
    return out;
}
std::ostream& operator<<(std::ostream& out, LineSeg const& line) {
    out<<line.start<<" -> "<<line.end;
    return out;
}
std::ostream& operator<<(std::ostream& out, Vents const& vents) {
    out<<vents.topLeft<<" x "<<vents.bottomRight;
    return out;
}
std::istream& operator>>(std::istream& in, LineSeg& point) {
    std::string ign;
    in>>point.start.x;
    in.ignore(); // ,
    in>>point.start.y;
    in.ignore(4); // _->_
    in>>point.end.x;
    in.ignore(); // ,
    in>>point.end.y;
    return in;
}
std::istream& operator>>(std::istream& in, Vents& vents) {
    do {
        LineSeg l;
        std::cin>>l;
        vents.lines.emplace_back(l);
        vents.topLeft.x = std::min({l.start.x, l.end.x, vents.topLeft.x});
        vents.topLeft.y = std::min({l.start.y, l.end.y, vents.topLeft.y});
        vents.bottomRight.x = std::max({l.start.x, l.end.x, vents.bottomRight.x});
        vents.bottomRight.y = std::max({l.start.y, l.end.y, vents.bottomRight.y});
    } while (!std::cin.eof());
    return in;
}