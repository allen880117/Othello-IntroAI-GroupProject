#pragma once
#include <utility>
/* Re-Define pair<int, int> as Coord */
typedef std::pair<int, int> Coord;
/* Define No Action */
#define NO_ACTION Coord(-1, -1)
/* Operator + */
Coord operator+(Coord lhs, Coord rhs);
/* Direction <r, c> */
extern Coord direction[8];