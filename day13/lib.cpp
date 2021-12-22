#include "lib.hpp"
#include <algorithm>
#include <string>
#include <sstream>
#include <regex>

bool operator<(Vector const& v1, Vector const& v2) {
    return v1.x < v2.x || ((v1.x == v2.x) && v1.y < v2.y);
}
bool operator==(Vector const& v1, Vector const& v2) {
    return v1.x == v2.x && v1.y == v2.y;
}
std::istream& operator>>(std::istream& in, Dot& dot) {
    in>>dot.x;
    in.ignore(1); //,
    in>>dot.y;
    return in;
}
std::ostream& operator<<(std::ostream& out, Dot const& dot) {
    out<<dot.x<<", "<<dot.y;
    return out;
}
std::istream& operator>>(std::istream& in, Dots& dots) {
    do {
        std::string s;
        in>>s;
        if (s.find(',') == -1 || in.eof())
            return in;
        
        std::stringstream ss; ss<<s;
        Dot dot; ss>>dot;
        dots.push_back(dot);
    } while (true);
    return in;
}
std::ostream& operator<<(std::ostream& out, Dots const& dots) {
    for(auto& dot: dots) {
        out<<dot<<std::endl;
    }
    return out;
}

std::istream& operator>>(std::istream& in, Fold& fold) {
    std::string s;
    in>>s;

    std::regex r("(x|y)=([0-9]+)");
    std::smatch m;
    std::regex_match(s, m, r);
    
    if (m.size() == 3) {
        if (m[1] == "x") {
            fold.x = std::stoi(m[2]);
            fold.y = 0;
        } else if (m[1] == "y") {
            fold.x = 0;
            fold.y = std::stoi(m[2]);
        }
    } else {
        fold.x = 0;
        fold.y = 0;
    }

    return in;
}
std::ostream& operator<<(std::ostream& out, Fold const& fold) {
    out<<"fold along x="<<fold.x<<", y="<<fold.y;
    return out;
}
std::istream& operator>>(std::istream& in, Folds& folds) {
    do {
        Fold fold;
        in>>fold;

        if (fold.x != 0 || fold.y != 0)
            folds.push_back(fold);
    } while (!in.eof());

    return in;
}
std::ostream& operator<<(std::ostream& out, Folds const& folds) {
    for(auto& fold: folds) {
        out<<fold<<std::endl;
    }
    return out;
}

void fold_up(int yaxis, Dots& dots) {
    auto ne = std::remove_if(dots.begin(), dots.end(), [yaxis](auto& dot) {
        return dot.y == yaxis;
    });
    dots.resize(std::distance(dots.begin(), ne));

    for(auto& dot: dots) {
        if (dot.y > yaxis) {
            dot.y = dot.y - 2*(dot.y - yaxis);
        }
    }
    
    std::sort(dots.begin(), dots.end());
    auto uq = std::unique(dots.begin(), dots.end());
    dots.resize(std::distance(dots.begin(), uq));
}

void fold_left(int xaxis, Dots& dots) {
    auto ne = std::remove_if(dots.begin(), dots.end(), [xaxis](auto& dot) {
        return dot.x == xaxis;
    });
    dots.resize(std::distance(dots.begin(), ne));

    for(auto& dot: dots) {
        if (dot.x > xaxis) {
            dot.x = dot.x - 2*(dot.x - xaxis);
        }
    }

    std::sort(dots.begin(), dots.end());
    auto uq = std::unique(dots.begin(), dots.end());
    dots.resize(std::distance(dots.begin(), uq));
}

void visualize(Dots const& dots) {
    int maxx = std::max_element(dots.begin(), dots.end(), [](auto d1, auto d2) { return d1.x <= d2.x;})->x;
    int maxy = std::max_element(dots.begin(), dots.end(), [](auto d1, auto d2) { return d1.y <= d2.y;})->y;

    

}
