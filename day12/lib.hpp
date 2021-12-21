#ifndef _LIB_HPP_
#define _LIB_HPP_

#include <algorithm>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <vector>

class Map {
    private:
    // original input
    std::unordered_map<int, std::vector<int>> map;

    // expended map with bidirectional connection
    std::unordered_map<int, std::vector<int>> path;

    // start = -1
    // end = -3
    // big cave: even number
    // small cave: odd number
    std::unordered_map<int, std::string> name;

    std::vector<std::vector<int>> tracks;
    std::vector<int> tracking;
    std::unordered_map<int, int> visited;

    void traverse(int from, int to, int twice=0, bool twice_on=false);

    public:
    void traverse(bool twice_on=false);
    size_t print_tracks(std::ostream& out);

    friend std::istream& operator>>(std::istream&, Map&);
    friend std::ostream& operator<<(std::ostream&, Map const&);
};

// std::istream& operator>>(std::istream&, Map&);
// std::ostream& operator<<(std::ostream&, Map const&);

#endif // _LIB_HPP_