#pragma once
#include <coord.h>
/* Game Utility */
namespace GameUtil {
bool is_end(Board &__board);
bool is_exist_valid_step(Board &__board, bool __is_black);
void do_set_and_flip(Board &__board, Coord __step);
int  get_result(Board &__board);
}  // namespace GameUtil
