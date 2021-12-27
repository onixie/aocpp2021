#ifndef _LIB_HPP_
#define _LIB_HPP_

#include <cstdint>
#include <vector>
#include <iostream>

using BITStream=std::vector<std::uint8_t>;

std::istream& operator>>(std::istream&, BITStream&);
std::ostream& operator<<(std::ostream&, BITStream const&);

#endif