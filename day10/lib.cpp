#include <cstddef>
#include <iostream>
#include <unordered_map>
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

const std::unordered_map<char, int> SCORE = {
    {'}', 1197},
    {']', 57},
    {')', 3},
    {'>', 25137},
};

void Line::clear() {
    data.clear();
    invalid = std::nullopt;
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
                //chunks.data.pop_back();
                std::string tmp;
                in>>tmp; //ignore the rest
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
    }
    return out;
}