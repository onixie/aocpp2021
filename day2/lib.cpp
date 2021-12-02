#include <iostream>
#include "lib.hpp"
namespace day2 {

std::ostream& operator<<(std::ostream& out, Dir const& dir) {
    switch(dir) {
        case Dir::Forward:
        out<<"forward";
        break;
        case Dir::Up:
        out<<"up";
        break;
        case Dir::Down:
        out<<"down";
        break;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, Command const& cmd) {
    return out<<cmd.dir<<" "<<cmd.moves;
}

std::istream& operator>>(std::istream& in, Dir& dir) {
    std::string tmp;
    in>>tmp;
    if (tmp == "forward") {
        dir = Dir::Forward;
    } else if (tmp == "up") {
        dir = Dir::Up;
    } else if (tmp == "down") {
        dir = Dir::Down;
    }
    return in;
}

std::istream& operator>>(std::istream& in, Command& cmd) {
    return in>>cmd.dir>>cmd.moves;
}
}