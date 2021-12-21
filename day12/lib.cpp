#include "lib.hpp"
#include <algorithm>
#include <cctype>
#include <ios>
#include <sstream>
#include <streambuf>
#include <string>
#include <unordered_map>

int assign_number(std::string const& s) {
    static std::unordered_map<std::string, int> numbering = {};
    static int odd = 1;
    static int even = 2;

    if (numbering.find(s) == numbering.end()) {
        if (s == "start") {
            numbering[s] = -1;
            return -1;
        }
        else if (s == "end") {
            numbering[s] = -3;
            return -3;
        }
        else if (std::all_of(s.cbegin(), s.cend(), [](auto c) { return std::isupper(c); })) {
            numbering[s] = even;
            even = even + 2;
            return even - 2;
        } else {
            numbering[s] = odd;
            odd = odd + 2;
            return odd - 2;
        }
    } else {
        return numbering[s];
    }
}

std::istream& operator>>(std::istream& in, Map& map) {
    do {
        std::string pname;

        std::getline(in, pname, '-');
        int left = assign_number(pname);
        map.name[left] = pname;

        std::getline(in, pname);
        int right = assign_number(pname);
        map.name[right] = pname;

        map.map[left].emplace_back(right);

        map.path[left].emplace_back(right);
        map.path[right].emplace_back(left);
    } while (!in.eof());
    return in;
}

std::ostream& operator<<(std::ostream& out, Map const& map) {
    for(auto& p: map.map) {
        for(auto& e: p.second)
        out<<map.name.at(p.first)<<"("<<p.first<<")-"<<map.name.at(e)<<"("<<e<<")"<<std::endl;
    }
    return out;
}

void Map::traverse(bool twice_on) {
    
    tracks.clear();
    tracking.clear();
    visited.clear();

    traverse(/* start */-1, /* end */-3, 0, twice_on);

    // remove some redundant path
    if (twice_on) {
        std::sort(tracks.begin(), tracks.end());
        auto iter = std::unique(tracks.begin(), tracks.end());
        tracks.resize(std::distance(tracks.begin(), iter));
    }
}

size_t Map::print_tracks(std::ostream& out) {
    for(auto& tk: tracks) {
        for(auto& s: tk) {
            out<<name.at(s)<<",";
        }
        out<<std::endl;
    }

    return tracks.size();
}

void Map::traverse(int from, int to, int twice, bool twice_on) {
    // if reach goal
    if (from == to) {
        tracking.push_back(to);
        tracks.push_back({});
        std::copy(tracking.cbegin(), tracking.cend(), std::back_inserter(tracks.back()));
        tracking.pop_back();
        return;
    }

    // if smaller cave and visited (deadend)
    if (from % 2 != 0 && 
        visited.find(from) != visited.end() && 
        visited.at(from) > ((twice_on && twice == from) ? 1 : 0)) {
        return;
    }

    // no next step (deadend)
    if (path.find(from) == path.end()) {
        return;
    }

    // otherwise
    if (visited.find(from) == visited.end())
        visited[from]=1;
    else
        visited[from]++;
    tracking.push_back(from);

    for(auto& next: path.at(from)) {
        traverse(next, to, twice, twice_on);

        // for a single small cave, if not try twice, try twice
        if (twice_on && next > 0 && next % 2 != 0 && twice == 0) {
            traverse(next, to, next, twice_on);
        }
    }

    tracking.pop_back();
    visited[from]--;
}