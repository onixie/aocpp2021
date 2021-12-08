#include "lib.hpp"

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