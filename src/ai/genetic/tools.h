//
// Created by dotty on 2/20/18.
//

#ifndef TAITRIS_TOOLS_H
#define TAITRIS_TOOLS_H

#include "../../core/board.h"
#include "../../core/game_state.h"

#define ABS(X) (((X) < 0) ? (-1 * (X)) : (X))

extern inline
size_t board_height(const struct board *brd, size_t x);

extern inline
void board_heights(const struct board *brd, size_t *heights);

extern inline
size_t bumpiness(const struct board *brd);
#endif //TAITRIS_TOOLS_H
