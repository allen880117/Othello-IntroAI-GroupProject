#include <coord.h>
Coord operator+(Coord lhs, Coord rhs) {
  return Coord(lhs.first + rhs.first, lhs.second + rhs.second);
}

Coord direction[8] = {Coord(-1, -1), Coord(-1, 0), Coord(-1, 1), Coord(0, -1),
                     Coord(0, 1),   Coord(1, -1), Coord(1, 0),  Coord(1, 1)};