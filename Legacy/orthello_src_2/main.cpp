#include "orthello.h"
using namespace std;

int main(int argc, char **argv) {
  Orthello ort;
  ort.start_game();
  printf("%s\n", GameControl::get_result(ort.board) == BLACK_WIN ? "BLACK WIN"
                                                                 : "WHITE WIN");
  return GameControl::get_result((ort.board));
}
