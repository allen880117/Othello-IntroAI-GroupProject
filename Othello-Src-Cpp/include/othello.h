#pragma once
#include <board.h>
#include <player.h>

/* Class Othello */
class Othello {
 private:
  Board  board;
  Player p1, p2;
  
  bool exist_valid_white;
  bool exist_valid_black;

 private:
  // Flow Control
  void do_pre_process();
  void do_main_process();
  void do_post_process();

  // Special Event
  void do_welcome_event();

  // Game Utility
  bool is_end();
  bool is_exist_valid_step(bool __is_black);
  void do_set_and_flip(Coord __step);

 public:
  void start_game();
};