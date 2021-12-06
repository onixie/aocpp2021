#ifndef _LIB_H_
#define _LIB_H_
#include <iostream>
#include <vector>
#include <algorithm>

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

struct Diagram {
    Diagram(Vents const& vents): Diagram(vents.bottomRight.x + 1, vents.bottomRight.y + 1) {}
    Diagram(uint width, uint height): data_(width * height), width_(width) {}
    
    uint& get(uint x, uint y) {
        return data_[y*width_+x];
    }
    
    uint count_cross() const {
        return std::count_if(this->data_.cbegin(), this->data_.cend(), [](auto c) {
            return c > 1;
        });
    }
    friend std::ostream& operator<<(std::ostream&, Diagram const&);

    private:
    std::vector<uint> data_;
    uint width_ = 0;
};

std::ostream& operator<<(std::ostream&, Point const&);
std::ostream& operator<<(std::ostream&, LineSeg const&);
std::ostream& operator<<(std::ostream&, Vents const&);
std::ostream& operator<<(std::ostream&, Diagram const&);
std::istream& operator>>(std::istream&, LineSeg&);
std::istream& operator>>(std::istream&, Vents&);
#endif //_LIB_H_