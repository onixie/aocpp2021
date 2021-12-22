#ifndef _LIB_HPP_
#define _LIB_HPP_

#include <cstdint>
#include <list>
#include <array>
#include <unordered_map>
#include <iostream>

#ifndef PROCESS
#define PROCESS 10
#endif

using Pair=std::array<char, 2>;

template<>
struct std::hash<Pair> {
    std::size_t operator()(const Pair& p) const;
};

using InsertRules = std::unordered_map<Pair, char, std::hash<Pair>>;
using PolyTemplate = std::list<Pair>;
using Counts = std::unordered_map<char, size_t>;
using PolyCounts = std::unordered_map<Pair, std::int64_t, std::hash<Pair>>;

std::istream& operator>>(std::istream&, Pair&);
std::ostream& operator<<(std::ostream&, Pair const&);

std::istream& operator>>(std::istream&, InsertRules&);
std::ostream& operator<<(std::ostream&, InsertRules const&);

std::istream& operator>>(std::istream&, PolyTemplate&);
std::ostream& operator<<(std::ostream&, PolyTemplate const&);
std::ostream& operator<<(std::ostream&, PolyCounts const&);

void process1(PolyTemplate& poly, InsertRules const& rules);
Counts count(PolyTemplate const& poly);

void init_counts(PolyTemplate const& temp, PolyCounts& poly, Counts& cnt);
void process1_opt(PolyCounts& poly, Counts& cnt, InsertRules const& rules);

#endif // _LIB_HPP_