#ifndef _LIB_HPP_
#define _LIB_HPP_
#include <string>
#include <array>
#include <tuple>
#include <iostream>
using Display = std::string;
using Pattern = std::string;
using Experiment = std::tuple<std::array<Pattern, 10>, std::array<Display, 4>>;

std::istream& operator>>(std::istream&, Experiment&);
std::ostream& operator<<(std::ostream&, Experiment const&);

#endif //_LIB_HPP_