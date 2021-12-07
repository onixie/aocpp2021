#ifndef _LIB_HPP_
#define _LIB_HPP_
#include <cstdint>
#include <vector>
#include <iostream>

using Crab = int;
using Submarines = std::vector<Crab>;

std::ostream& operator<<(std::ostream&, Submarines const&);
std::istream& operator>>(std::istream&, Submarines&);

#endif //_LIB_HPP_