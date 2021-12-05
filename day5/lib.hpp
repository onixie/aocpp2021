#ifndef _LIB_H_
#define _LIB_H_
#include <iostream>
#include <vector>

struct Point {
    uint x; uint y;
};

struct LineSeg {
    Point start; Point end;
};

struct Vents {
    std::vector<LineSeg> lines;
    Point topLeft;
    Point bottomRight;
};

std::ostream& operator<<(std::ostream&, Point const&);
std::ostream& operator<<(std::ostream&, LineSeg const&);
std::ostream& operator<<(std::ostream&, Vents const&);
std::istream& operator>>(std::istream&, LineSeg&);
std::istream& operator>>(std::istream&, Vents&);
#endif //_LIB_H_