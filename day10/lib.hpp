#ifndef _LIB_HPP_
#define _LIB_HPP_

#include <vector>
#include <optional>
#include <tuple>
#include <unordered_map>
#include <iostream>

struct Line{
    std::vector<char> data = {};
    std::optional<std::tuple<char, char>> invalid = std::nullopt;
    void clear();
};

extern const std::unordered_map<char, int> SCORE;
std::istream& operator>>(std::istream& in, Line& chunks);
std::ostream& operator<<(std::ostream& out, Line const& chunks);

#endif // _LIB_HPP_