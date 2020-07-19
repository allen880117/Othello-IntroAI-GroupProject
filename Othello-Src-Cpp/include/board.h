#pragma once
#include <array>

/* Color Definition */
#define B_GREEN_F_BLACK "\033[0;30;42m"
#define B_BLACK "\033[0;40m"
#define B_WHITE "\033[0;47m"
#define W_NORMAL "\033[0m"
#define W_CLEAR "\033[2J\033[1;1H"

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

  void print();
  void clear();
  bool check_boundary(int __x, int __y);
};