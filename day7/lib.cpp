#include "lib.hpp"

std::ostream& operator<<(std::ostream& out, Submarines const& submarines) {
    for(auto iter = submarines.cbegin(); iter < submarines.cend(); iter++) {
        out<<(*iter);
        if (iter+1 < submarines.cend())
            out<<", ";
    }
    return out;
}

std::istream& operator>>(std::istream& in, Submarines& submarines) {
    Crab c = 0;

    do {
        in>>c;
        submarines.push_back(c);
        in.ignore(); //,
    } while( !in.eof() );

    return in;
}