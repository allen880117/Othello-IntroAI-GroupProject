#include <player.h>

/*
    Default Constructor
*/
Player::Player() {
  this->is_cpu   = true;
  this->is_black = true;
}

/*
    Constructor with arguments
*/
Player::Player(bool _is_cpu, bool _is_black) {
  this->is_cpu   = _is_cpu;
  this->is_black = _is_black;
}

/*
    Set Color
*/
void Player::set_color(bool _is_black) { this->is_black = _is_black; }

/*
    Set Computer Played Unit
*/
void Player::set_cpu(bool _is_cpu) { this->is_cpu = _is_cpu; }

/*
    Get Step
*/
Coord Player::get_step(Board &_board) {
  Coord step = NO_ACTION;
  if (this->is_cpu) {
      // Do UCT Search
  } else {
      // Ask User to Input
  }
}