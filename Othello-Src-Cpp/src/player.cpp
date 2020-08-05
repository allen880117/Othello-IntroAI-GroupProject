#include <game_util.h>
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
    // Color is the Last Piece's Color
    step = uct.uct_search(_board, !this->is_black);
  } else {
    // Ask User to Input
    while (true) {
      int r, c;
      printf("Please input valid step in format < r , c >: ");
      scanf("%d %d", &r, &c);
      step = Coord(r, c);
      if (GameUtil::is_valid_step(_board, this->is_black, step)) break;
    }
  }
  return step;
}