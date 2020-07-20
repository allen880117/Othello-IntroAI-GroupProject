#include <coord.h>
Coord operator+(Coord lhs, Coord rhs) {
  return Coord(lhs.first + rhs.first, lhs.second + rhs.second);
}