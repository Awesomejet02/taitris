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

#define DEBUG_STATE_NAME "State"
#define DEBUG_STATE_COLOR ANSI_FG_MAGENTA
#define DEBUG_STATE_TAG DEBUG_TAG(DEBUG_STATE_NAME, DEBUG_STATE_COLOR)

void debug_state_print_line_number(const Board *brd, int y);

void debug_state_print_cell(Cell c);

void debug_state_print_infos(const State *state, int y);

void debug_state_print_next_piece(const Piece *pc, int y);

void debug_state_print(const State *state);

#endif //TAITRIS_DEBUG_STATE_H
