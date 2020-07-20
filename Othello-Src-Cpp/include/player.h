#pragma once
#include <board.h>
#include <coord.h>

/* Class Player */
class Player {
 private:
  bool is_cpu;
  bool is_black;

 public:
  void  set_color(bool __is_black);
  bool  is_cpu();
  Coord get_step(Board &__board);
};