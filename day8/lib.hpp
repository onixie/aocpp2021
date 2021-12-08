#ifndef _LIB_HPP_
#define _LIB_HPP_
#include <string>
#include <array>
#include <tuple>
#include <iostream>
#include <unordered_map>

using Display = std::string;
using Pattern = std::string;
using Experiment = std::tuple<std::array<Pattern, 10>, std::array<Display, 4>>;
using Knowledge1 = std::unordered_map<int /* num of segments */, int /* display digit */>;
using Knowledge2 = std::unordered_map<int /* display digit */, std::string /* segments */>;

std::istream& operator>>(std::istream&, Experiment&);
std::ostream& operator<<(std::ostream&, Experiment const&);

#endif //_LIB_HPP_