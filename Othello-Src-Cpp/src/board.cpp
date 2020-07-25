#include <board.h>

/*
    Constructor
*/
Board::Board() { this->clear(); }

/*
    Operator ==
*/
bool Board::operator==(const Board &rhs) { return (this->board == rhs.board); }

/*
    Operator =
*/
void Board::operator=(const Board &rhs) { this->board = rhs.board; }

/*
    Get Status of the Cell of the Board
*/
Status Board::get(int _x, int _y) {
  if (this->check_boundary(_x, _y))
    return this->board.at(_x).at(_y);
  else
    return Status::ILLEGAL;
}

/*
    Set Status of the Cell of the Board
*/
bool Board::set(int _x, int _y, Status _status) {
  if (this->check_boundary(_x, _y)) {
    this->board.at(_x).at(_y) = _status;
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
bool Board::check_boundary(int _x, int _y) {
  return (0 <= _x) && (_x < BOARD_H) && (0 <= _y) && (_y < BOARD_W);
}