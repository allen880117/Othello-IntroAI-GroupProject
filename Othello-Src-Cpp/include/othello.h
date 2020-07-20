#pragma once
#include <board.h>
#include <coord.h>
#include <player.h>
#include <game_util.h>

/* Class Othello */
class Othello {
 private:
  Board  board;
  Player player_black;
  Player player_white;

 private:
  // Flow Control
  void do_pre_process();
  void do_main_process();
  void do_post_process();

  // Special Event
  void do_welcome_event();

 public:
  void start_game();
};