#pragma once
#include <board.h>
#include <coord.h>
#include <uct.h>

/* Class Player */
class Player {
 private:
  bool is_cpu;
  bool is_black;
  
  UCT::Tree uct;

 public:
  Player();
  Player(bool _is_cpu, bool _is_black);
  void  set_color(bool _is_black);
  void  set_cpu(bool _is_cpu);
  Coord get_step(Board &_board);
};