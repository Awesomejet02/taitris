/**
 * @file    debug_state.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Debug state
 */
#ifndef TAITRIS_DEBUG_STATE_H
#define TAITRIS_DEBUG_STATE_H

#include <stdio.h>

#include "../debug.h"
#include "../../engine/state.h"
#include "../../utils/ansi_code.h"
#include "../../ai/genetic/engine.h"

#define DEBUG_STATE_NAME "State"
#define DEBUG_STATE_COLOR ANSI_FG_MAGENTA
#define DEBUG_STATE_TAG DEBUG_TAG(DEBUG_STATE_NAME, DEBUG_STATE_COLOR)

void debug_state_print(const State *state);

#endif //TAITRIS_DEBUG_STATE_H
