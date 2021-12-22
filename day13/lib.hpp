#ifndef _LIB_HPP_
#define _LIB_HPP_
#include <iostream>
#include <vector>

struct Vector {
    int x; int y;
};

struct Dot: Vector {};
struct Fold: Vector {};

using Dots  = std::vector<Dot>;
using Folds = std::vector<Fold>;

bool operator<(Vector const&, Vector const&);
bool operator==(Vector const&, Vector const&);
std::istream& operator>>(std::istream&, Dot&);
std::ostream& operator<<(std::ostream&, Dot const&);
std::istream& operator>>(std::istream&, Dots&);
std::ostream& operator<<(std::ostream&, Dots const&);

std::istream& operator>>(std::istream&, Fold&);
std::ostream& operator<<(std::ostream&, Fold const&);
std::istream& operator>>(std::istream&, Folds&);
std::ostream& operator<<(std::ostream&, Folds const&);

void fold_up(int, Dots&);
void fold_left(int, Dots&);
#endif //_LIB_HPP_