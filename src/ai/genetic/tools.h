//
// Created by dotty on 2/20/18.
//

#ifndef TAITRIS_TOOLS_H
#define TAITRIS_TOOLS_H

#include <stdio.h>
#include "../../engine/state.h"
#include "../../utils/ansi_code.h"

#define ABS(X) (((X) < 0) ? (-1 * (X)) : (X))

size_t board_height(const Board *brd, size_t x);

void board_heights(const Board *brd, size_t *heights);

size_t bumpiness(const Board *brd);

size_t aggregate_height(const Board *brd);

size_t hole(const Board *brd, size_t x);

size_t holes(const Board *brd);

size_t coalescent_clears(const Board *brd);

size_t clears(const Board *brd);

void show_features(const Board *brd);
#endif //TAITRIS_TOOLS_H
