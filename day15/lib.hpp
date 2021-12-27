#ifndef _LIB_HPP_
#define _LIB_HPP_

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <queue>
#include <functional>
#include <iterator>
#include <limits>
#include <vector>
#include <iostream>
#include <queue>

struct Chiton {
    Chiton(std::int8_t risk, int x, int y): 
        risk(risk), 
        total_risk(std::numeric_limits<size_t>::max()), 
        x(x), 
        y(y), 
        visited(false)
    {}
    std::int8_t risk;
    size_t total_risk;
    int x; int y;
    bool visited;
    operator int() const {
        return static_cast<int>(total_risk);
    }
};

struct Cavern {
    std::vector<std::vector<Chiton>> chitons = {{}};
    int width = 0;
    int height = 0;
};

// a min heap with min total_risk chitons at front
struct MinChitons : std::vector<Chiton*> {
    void push_back(Chiton* cp);
    void pop_back();
    void rebalance();
};

std::istream& operator>>(std::istream&, Cavern&);
std::ostream& operator<<(std::ostream&, Cavern const&);

int dijkstra(Cavern& cave, MinChitons& mins);

#endif // _LIB_HPP_