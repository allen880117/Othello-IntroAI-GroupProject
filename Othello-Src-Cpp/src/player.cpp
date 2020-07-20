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
Player::Player(bool __is_cpu, bool __is_black) {
  this->is_cpu   = __is_cpu;
  this->is_black = __is_black;
}

/*
    Set Color
*/
void Player::set_color(bool __is_black) { this->is_black = __is_black; }

/*
    Set Computer Played Unit
*/
void Player::set_cpu(bool __is_cpu) { this->is_cpu = __is_cpu; }

/*
    Get Step
*/
Coord Player::get_step(Board &__board) {
  Coord step = NO_ACTION;
  if (this->is_cpu) {
      // Do UCT Search
  } else {
      // Ask User to Input
  }
}