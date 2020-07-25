#pragma once
#include <board.h>
#include <coord.h>

#include <array>
#include <string>
/* Class : Weight */

class Weight {
 private:
  std::array<std::array<double, BOARD_W>, BOARD_H> weight;

 public:
  Weight();
  void   reset();
  void   set(int _r, int _c, double _value);
  void   set(Coord _step, double _value);
  double get(int _r, int _c);
  double get(Coord _step);
};