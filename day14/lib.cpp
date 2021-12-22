#include "lib.hpp"
#include <algorithm>
#include <array>
#include <cstdio>
#include <string>
#include <unordered_map>
#include <utility>
#include <regex>
#include <sstream>

std::size_t std::hash<Pair>::operator()(const Pair& p) const
{
    return std::hash<char>()(p[0])
        ^ (std::hash<char>()(p[1])<<1);
}

std::istream& operator>>(std::istream& in, Pair& p) {
    char c1; in>>c1;
    char c2 = in.peek();
    
    p[0] = c1;
    p[1] = c2;
    return in;
}


std::ostream& operator<<(std::ostream& out, Pair const& p) {
    out<<p[0]<<p[1];
    return out;
}

std::istream& operator>>(std::istream& in, InsertRules& rules) {
    static std::regex re(" *-> *([A-Z])");

    do {
        Pair p; in>>p; // also skip any empty line ahead
        in.ignore(); // progress two the second char in pair

        std::string tmp;
        std::getline(in, tmp);
        if (tmp == "")
            break;

        std::smatch sm;
        std::regex_match(tmp, sm, re);

        if (sm.size() == 2) {
            char ic = sm[1].str()[0];
            rules.emplace(p, ic);
        } else {
            std::cerr<<"Invalid insertion rule detected: "<<p<<tmp<<std::endl;
        }
    } while (true);
    return in;
}
std::ostream& operator<<(std::ostream& out, InsertRules const& rules) {
    for(auto& rule : rules) {
        out<<rule.first<<" -> "<<rule.second<<std::endl;
    }
    return out;
}
std::istream& operator>>(std::istream& in, PolyTemplate& poly) {
    std::string s;
    std::getline(in, s);
    std::stringstream ss;
    ss<<s;
    do {
        Pair p; ss>>p;
        if (ss.eof())
            break;
        poly.push_back(p);
    } while (true);
    return in;
}
std::ostream& operator<<(std::ostream& out, PolyTemplate const& poly) {
    out<<poly.front()[0];
    for(auto& p: poly) {
        out<<p[1];
    }
    return out;
}
std::ostream& operator<<(std::ostream& out, PolyCounts const& poly) {
    for(auto& p: poly) {
        out<<p.first<<" "<<p.second<<std::endl;
    }
    return out;
}
void process1(PolyTemplate& poly, InsertRules const& rules) {
    for(auto iter = poly.begin(); iter != poly.end(); iter++) {
        decltype(rules.end()) found;
        if ((found = rules.find(*(iter))) != rules.end()) {
            // replace the original pair with the new pairs
            
            poly.insert(iter, {found->first[0], found->second});

            (*iter)[0] = found->second;
            (*iter)[1] = found->first[1];
        }
    }
}

Counts count(PolyTemplate const& poly) {
    Counts cnts;

    cnts[poly.front()[0]]++;
    for(auto& p: poly){
        cnts[p[1]]++;
    }

    return cnts;
}

void init_counts(PolyTemplate const& temp, PolyCounts& poly, Counts& cnt) {
    cnt = count(temp);
    for(auto iter = temp.begin(); iter != temp.end(); iter++) {
        poly[(*iter)]++;
    }
}

void process1_opt(PolyCounts& poly, Counts& cnt, InsertRules const& rules) {
    static std::array<char, 2> f;
    PolyCounts tmp;
    for(auto iter = poly.begin(); iter != poly.end(); iter++) {
        decltype(rules.end()) found;
        if ((found = rules.find(iter->first)) != rules.end()) {
            // replace the original pair with the new pairs repecting its count
            tmp[iter->first] -= iter->second;

            f[0] = found->first[0];
            f[1] = found->second;
            tmp[f] += iter->second;

            f[0] = found->second;
            f[1] = found->first[1];
            tmp[f] += iter->second;

            // update the count of the element
            cnt[found->second] += iter->second;
        }
    }

    // update back
    for(auto iter = tmp.begin(); iter != tmp.end(); iter++) {
        poly[iter->first] += iter->second;
    }
}

