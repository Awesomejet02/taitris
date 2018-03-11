/**
 * @file    state.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   No description
 */
#include "state.h"

State *state_create() {
  State *state = malloc(sizeof(State));

  if (state == NULL)
    errx(EXIT_FAILURE, "Can't initialize state object");

  memset(state, 0, sizeof(State));

  state->board = board_create(BOARD_WIDTH, BOARD_HEIGHT);

  return state;
}

void state_init(State *state) {
  assert(state != NULL);

  state->score = 0;
  state->level = 1;
  state->broken_lines = 0;
  state->step = 0;
  state->input_counts = 0;

  board_init(state->board);

  state->current_piece = piece_random(SPAWN_X, SPAWN_Y, ANGLE_UP);
  state->next_piece = piece_random(SPAWN_X, SPAWN_Y, ANGLE_UP);
}

void state_free(State *state) {
  assert(state != NULL);

  board_free(state->board);
  piece_free(state->current_piece);
  piece_free(state->next_piece);
  free(state);
}

State *state_copy(const State *state) {
  assert(state);

  State *cstate = state_create();
  memcpy(cstate, state, sizeof(State));

  cstate->board = board_copy(state->board);

  cstate->current_piece = piece_copy(state->current_piece);
  cstate->next_piece = piece_copy(state->next_piece);

  return cstate;
}