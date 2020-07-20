#include <board.h>

/*
    Constructor
*/
Board::Board() { this->clear(); }

/*
    Get Status of the Cell of the Board
*/
Status Board::get(int __x, int __y) {
  if (this->check_boundary(__x, __y))
    return this->board.at(__x).at(__y);
  else
    return Status::ILLEGAL;
}

/*
    Set Status of the Cell of the Board
*/
bool Board::set(int __x, int __y, Status __status) {
  if (this->check_boundary(__x, __y)) {
    this->board.at(__x).at(__y) = __status;
    return true;
  } else {
    return false;
  }
}

/*
    Clear the Board
*/
void Board::clear() {
  for (uint i = 0; i < BOARD_H; i++)
    for (uint j = 0; j < BOARD_W; j++)
      this->board.at(i).at(j) = Status::UNOCCUPIED;

  this->board.at(0).at(0)                     = Status::ILLEGAL;
  this->board.at(0).at(BOARD_W - 1)           = Status::ILLEGAL;
  this->board.at(BOARD_H - 1).at(0)           = Status::ILLEGAL;
  this->board.at(BOARD_H - 1).at(BOARD_W - 1) = Status::ILLEGAL;
}

/*
    Check whether the coordinate is inside board or not
*/
bool Board::check_boundary(int __x, int __y) {
  return (0 <= __x) && (__x < BOARD_H) && (0 <= __y) && (__y < BOARD_W);
}