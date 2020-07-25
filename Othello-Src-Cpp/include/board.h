#pragma once
#include <array>
/* Status of Board */
enum class Status { UNOCCUPIED = 0, BLACK, WHITE, ILLEGAL };

/* Board Size */
#define BOARD_H 8
#define BOARD_W 8

/* Class Board */
class Board {
 private:
  std::array<std::array<Status, BOARD_W>, BOARD_H> board;

 public:
  Board();
  bool operator==(const Board &rhs);
  void operator=(const Board &rhs);

  Status get(int _x, int _y);
  bool   set(int _x, int _y, Status _status);

  void clear();
  bool check_boundary(int _x, int _y);
};