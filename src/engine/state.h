/**
 * @file    state.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   State
 */
#ifndef TAITRIS_STATE_H
#define TAITRIS_STATE_H

#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <assert.h>

#include "board.h"
#include "piece/piece.h"
#include "piece/piece_shape.h"
#include "piece/piece_queue.h"
#include "motion.h"
#include "../utils/safe_op.h"

typedef struct {
  unsigned int score;
  unsigned int level;
  unsigned int broken_lines;
  unsigned int step;
  unsigned int input_counts;

  Board *board;

  PieceQueue *piece_queue;
  size_t piece_queue_index;

  Piece *current_piece;
  Piece *next_piece;
} State;

static inline
void state_add_score(State *state, unsigned int score) {
  assert(state != NULL);
  if (score == 0) return;

  if (safe_uint_add(state->score, score, &state->score) != SAFE_OP_SUCCESS)
    errx(EXIT_FAILURE, "State add score overflow detected %u + %u",
         state->score, score);
}

static inline
void state_add_level(State *state, unsigned int level) {
  assert(state != NULL);
  if (level == 0) return;

  if (safe_uint_add(state->level, level, &state->level) != SAFE_OP_SUCCESS)
    errx(EXIT_FAILURE, "State add level overflow detected %u + %u",
         state->level, level);
}

static inline
void state_add_broken_lines(State *state, unsigned int broken_lines) {
  assert(state != NULL);
  if (broken_lines == 0) return;

  if (safe_uint_add(state->broken_lines, broken_lines, &state->broken_lines) !=
      SAFE_OP_SUCCESS)
    errx(EXIT_FAILURE, "State add broken_lines overflow detected %u + %u",
         state->broken_lines, broken_lines);
}

static inline
void state_add_step(State *state, unsigned int step) {
  assert(state != NULL);
  if (step == 0) return;

  if (safe_uint_add(state->step, step, &state->step) != SAFE_OP_SUCCESS)
    errx(EXIT_FAILURE, "State add step overflow detected %u + %u",
         state->step, step);
}

static inline
void state_add_input_counts(State *state, unsigned int input_counts) {
  assert(state != NULL);
  if (input_counts == 0) return;

  if (safe_uint_add(state->input_counts, input_counts, &state->input_counts) !=
      SAFE_OP_SUCCESS)
    errx(EXIT_FAILURE, "State add input_counts overflow detected %u + %u",
         state->input_counts, input_counts);
}

State *state_create();

void state_init(State *state, PieceQueue *q);

void state_free(State *state);

State *state_copy(const State *state);

Piece *state_create_piece(State *state);

void state_next_piece(State *state);

int state_step(State *state);

static inline
Cell state_at(const State *state, int x, int y) {
  assert(state != NULL);
  assert(x >= 0);
  assert(x < state->board->width);
  assert(y >= 0);
  assert(y < (state->board->height + BOARD_HIDDEN));

  Piece *pc = state->current_piece;
  int px = x - pc->x;
  int py = pc->y - y;

  if (px >= 0 && py >= 0 &&
      px < PIECE_SHAPE_WIDTH && py < PIECE_SHAPE_HEIGHT &&
      pc->shape->shape[pc->angle][py][px] != CELL_EMPTY)
    return pc->shape->fill;

  if (y < state->board->height)
    return board_at(state->board, x, y);

  return CELL_EMPTY;
}

#endif //TAITRIS_STATE_H
