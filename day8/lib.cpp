#include "lib.hpp"
#include <ostream>
#include <unordered_map>

std::istream& operator>>(std::istream& in, Experiment& exp) 
{
    for(int i = 0; i < 10; i++) 
        in >> std::get<0>(exp)[i];

    in.ignore(10, '|');

    for(int i = 0; i < 4; i++)
        in >> std::get<1>(exp)[i];

    return in;
}

std::ostream& operator<<(std::ostream& out, Experiment const& exp)
{
    for(auto pat : std::get<0>(exp)) {
        out<<pat<<" ";
    }
    out<<"|";
    for(auto dsp : std::get<1>(exp)) {
        out<<" "<<dsp;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, Knowledge2 const& know) {
    for(auto k : know) {
        out<<k.first<<":";
        for(auto c : k.second) {
            out<<" "<<c;
        }
        out<<std::endl;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, Knowledge3 const& know) {
    for(auto k : know) {
        out<<k.first<<": "<<k.second;
        out<<std::endl;
    }
    return out;
}

Knowledge1 knowledge1 = { 
    { 6, 0 }, 
    { 2, 1 }, 
    { 5, 2 }, 
    { 5, 3 }, 
    { 4, 4 }, 
    { 5, 5 }, 
    { 6, 6 }, 
    { 3, 7 }, 
    { 7, 8 },
    { 6, 9 }, 
};
