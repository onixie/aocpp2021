#include <cstddef>
#include <vector>
#include "lib.hpp"

const std::unordered_map<char, char> OPEN = {
    {'{', '}'},
    {'[', ']'},
    {'(', ')'},
    {'<', '>'},
};

const std::unordered_map<char, char> CLOSE = {
    {'}', '{'},
    {']', '['},
    {')', '('},
    {'>', '<'},
};

void Line::clear() {
    data = {};
    invalid = std::nullopt;
}

std::vector<char> Line::ac() const {
    if (invalid != std::nullopt)
        return {};
    
    std::vector<char> res;
    for(auto riter = data.crbegin(); riter != data.crend(); riter++) {
        res.push_back(OPEN.at(*riter));
    }
    return res;
}

std::istream& operator>>(std::istream& in, Line& chunks) {
    do {
        char c; in.get(c);
        if (c == '\n' || c == '\r' || in.eof())
            return in;

        if (OPEN.find(c) != OPEN.end()) { // opening
            chunks.data.push_back(c);
            continue;
        }
        
        if (CLOSE.find(c) != CLOSE.end()) {// opening
            if (CLOSE.at(c) == chunks.data.back()) {
                chunks.data.pop_back();
            } else {
                chunks.invalid = { /* expect */ OPEN.at(chunks.data.back()), /* found */c };
                std::string tmp; in>>tmp; //ignore the rest
                in.get(c); //ignore the newline
                return in;
            }
        }
    } while(true);
    return in;
}

std::ostream& operator<<(std::ostream& out, Line const& chunks) {
    for(auto& c: chunks.data) {
        out<<c;
    }
    if (chunks.invalid != std::nullopt) {
        auto err = *chunks.invalid;
        out<<" err! expect: "<<std::get<0>(err)<<", found:"<<std::get<1>(err);
    } else {
        out<<" ac: ";
        auto cs = chunks.ac();
        for(auto& c: cs) out<<c;
    }
    return out;
}