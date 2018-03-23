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

int board_height(const State *brd, int x);

void board_heights(const State *state, int *heights);

int bumpiness(const State *state);

int aggregate_height(const State *state);

int hole(const State *state, int x);

int holes(const State *state);

//size_t coalescent_clears(const State *state);

int clears(const State *state);

void show_features(const State *state);
#endif //TAITRIS_TOOLS_H
