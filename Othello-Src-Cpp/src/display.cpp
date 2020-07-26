#include <board.h>
#include <display.h>
#include <cstdio>

/*
    Clear the Screen
*/
void Display::clear() { printf(CLEAR); }

/*
    Print the board
*/
template <>
void Display::print(Board &_board) {
  printf("  ");
  for (int i=0; i< BOARD_W; i++) printf("%d ", i);
  printf("\n");

  for (int i = 0; i < BOARD_H; i++) {
    printf(NORMAL " ");
    for (int k = 0; k < BOARD_W * 2 + 1; k++) printf(B_GREEN_F_BLACK "=");
    printf("\n" NORMAL);

    printf(NORMAL "%d", i);

    for (int j = 0; j < BOARD_W; j++) {
      Status status = _board.get(i, j);
      switch (status) {
        case Status::ILLEGAL:
          printf(B_GREEN_F_BLACK "|X");
          break;
        case Status::BLACK:
          printf(B_GREEN_F_BLACK "|" B_BLACK " ");
          break;
        case Status::WHITE:
          printf(B_GREEN_F_BLACK "|" B_WHITE " ");
          break;
        default:
          printf(B_GREEN_F_BLACK "| ");
          break;
      }
    }

    printf(B_GREEN_F_BLACK "|\n");
  }

  printf(NORMAL " ");
  for (int k = 0; k < BOARD_W * 2 + 1; k++) printf(B_GREEN_F_BLACK "=");
  printf("\n" NORMAL);
}