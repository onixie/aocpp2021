#include "lib.hpp"

std::ostream& operator<<(std::ostream& out, SchoolOfFish const& school) {
    for(auto iter = school.cbegin(); iter < school.cend(); iter++) {
        out<<(*iter);
        if (iter+1 < school.cend())
            out<<", ";
    }
    return out;
}

std::istream& operator>>(std::istream& in, SchoolOfFish& school) {
    LanternFish f = 0;

    do {
        in>>f;
        school.push_back(f);
        in.ignore(); //,
    } while( !in.eof() );

    return in;
}