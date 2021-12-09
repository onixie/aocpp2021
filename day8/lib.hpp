#ifndef _LIB_HPP_
#define _LIB_HPP_
#include <string>
#include <array>
#include <tuple>
#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>

using Display = std::string;
using Pattern = std::string;
using Experiment = std::tuple<std::array<Pattern, 10>, std::array<Display, 4>>;
using Knowledge1 = std::unordered_map<int /* num of segments */, int /* display digit */>;
using Knowledge2 = std::unordered_map<int /* display digit */, std::set<char> /* segments */>;
using Knowledge3 = std::unordered_map<char /* origin */, char /* now */>;

std::istream& operator>>(std::istream&, Experiment&);
std::ostream& operator<<(std::ostream&, Experiment const&);
std::ostream& operator<<(std::ostream&, Knowledge2 const&);
std::ostream& operator<<(std::ostream&, Knowledge3 const&);

extern Knowledge1 knowledge1;

#endif //_LIB_HPP_