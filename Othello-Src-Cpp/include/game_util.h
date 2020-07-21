#pragma once
#include <coord.h>
#include <board.h>
/* Game Utility */
namespace GameUtil {
bool is_end(Board &__board);
bool is_valid_step(Board &__board, bool __is_black, Coord __step);
bool do_set_and_flip(Board &__board, bool __is_black, Coord __step);
int  get_result(Board &__board);
}  // namespace GameUtil
