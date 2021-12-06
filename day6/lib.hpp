#ifndef _LIB_HPP_
#define _LIB_HPP_
#include <cstdint>
#include <vector>
#include <iostream>

using LanternFish = int;
using SchoolOfFish = std::vector<LanternFish>;

std::ostream& operator<<(std::ostream&, SchoolOfFish const&);
std::istream& operator>>(std::istream&, SchoolOfFish&);

#endif //_LIB_HPP_