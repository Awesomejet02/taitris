/**
 * @file    debug_genetic.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Genetic algorithm debuging
 */
#ifndef TAITRIS_DEBUG_GENETIC_H
#define TAITRIS_DEBUG_GENETIC_H

#include <stdio.h>

#include "../debug.h"
#include "../../utils/ansi_code.h"
#include "../../engine/state.h"
#include "../../ai/genetic/tools.h"
#include "../../ai/genetic/engine.h"

#define DEBUG_STATE_NAME "Genetic"
#define DEBUG_STATE_COLOR ANSI_FG_BLUE
#define DEBUG_STATE_TAG DEBUG_TAG(DEBUG_STATE_NAME, DEBUG_STATE_COLOR)

void debug_genetic_print_stats(const State *state);

#endif //TAITRIS_DEBUG_GENETIC_H
