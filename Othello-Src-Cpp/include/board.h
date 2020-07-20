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
  Status get(int __x, int __y);
  bool   set(int __x, int __y, Status __status);

  void clear();
  bool check_boundary(int __x, int __y);
};