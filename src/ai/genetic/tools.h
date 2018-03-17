/**
 * @file    tools.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Tools for the genetic algorithm
 */

#ifndef TAITRIS_TOOLS_H
#define TAITRIS_TOOLS_H

#include <stdio.h>
#include "../../engine/state.h"
#include "../../utils/ansi_code.h"

#define ABS(X) (((X) < 0) ? (-1 * (X)) : (X))

int board_height(const Board *brd, int x);

void board_heights(const Board *brd, int *heights);

int bumpiness(const Board *brd);

int aggregate_height(const Board *brd);

int hole(const Board *brd, int x);

int holes(const Board *brd);

size_t coalescent_clears(const Board *brd);

int clears(const Board *brd);

void show_features(const Board *brd);
#endif //TAITRIS_TOOLS_H
