#pragma once
#include <board.h>
#include <coord.h>
#include <vector>
/* Game Utility */
namespace GameUtil {
bool               is_end(Board &_board);
bool               is_valid_step(Board &_board, bool _is_black, Coord _step);
bool               do_set_and_flip(Board &_board, bool _is_black, Coord _step);
std::vector<Coord> get_valid_steps(Board &_board, bool _is_black);
int                get_result(Board &_board);
}  // namespace GameUtil
