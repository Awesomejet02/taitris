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

int genetic_tools_height(const State *state, int x);

void genetic_tools_heights(const State *state, int *heights);

int genetic_tools_bumpiness(const State *state);

int genetic_tools_aggregate_height(const State *state);

int genetic_tools_hole(const State *state, int x);

int genetic_tools_holes(const State *state);

int genetic_tools_clears(const State *state);

#endif //TAITRIS_TOOLS_H
