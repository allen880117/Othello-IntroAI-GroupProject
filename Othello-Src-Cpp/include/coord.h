#pragma once
#include <utility>
/* Re-Define pair<int, int> as Coord */
typedef std::pair<int, int> Coord;
/* Define No Action */
#define NO_ACTION Coord(-1, -1)
/* Operator + */
Coord operator+(Coord lhs, Coord rhs);
/* Direction <r, c> */
Coord direction[] = {Coord(-1, -1), Coord(-1, 0), Coord(-1, 1),
                       Coord(0, -1),  Coord(0, 1),  Coord(1, -1),
                       Coord(1, 0),   Coord(1, 1)};