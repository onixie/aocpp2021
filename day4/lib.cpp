#include "lib.hpp"
#include <sstream>
#include <string>

std::ostream& operator<<(std::ostream& out, Numbers const& numbers) {
    std::stringstream ss;
    for (auto iter = numbers.list.cbegin(); iter < numbers.list.cend(); iter++) {
        ss<<*iter;
        if (std::distance(iter, numbers.list.cend()) > 1)
            ss<<",";
    }
    out<<ss.str();
    return out;
}

std::ostream& operator<<(std::ostream& out, Boards const& boards);

std::istream& operator>>(std::istream& in, Numbers& numbers) {
    std::string tmp;
    while(getline(in, tmp, ','))
        numbers.list.emplace_back(std::stoi(tmp));
    return in;
}
std::istream& operator>>(std::istream& in, Boards& boards);