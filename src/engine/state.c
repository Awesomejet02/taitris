/**
 * @file    state.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   State
 */
#include "state.h"
#include "board.h"

State *state_create() {
  State *state = malloc(sizeof(State));

  if (state == NULL)
    errx(EXIT_FAILURE, "Can't initialize state object");

  memset(state, 0, sizeof(State));

  state->board = board_create(BOARD_WIDTH, BOARD_HEIGHT);

  return state;
}

void state_init(State *state, PieceQueue *q) {
  assert(state != NULL);
  assert(q != NULL);

  state->score = 0;
  state->level = 1;
  state->broken_lines = 0;
  state->step = 0;
  state->input_counts = 0;

  board_init(state->board);

  state->piece_queue = q;
  state->piece_queue_index = 0;

  state_next_piece(state);
}

void state_free(State *state) {
  assert(state != NULL);

  board_free(state->board);
  piece_free(state->current_piece);
  piece_free(state->next_piece);
  free(state);
}

State *state_copy(const State *state) {
  assert(state != NULL);

  State *cstate = state_create();
  memcpy(cstate, state, sizeof(State));

  cstate->board = board_copy(state->board);

  cstate->current_piece = piece_copy(state->current_piece);
  cstate->next_piece = piece_copy(state->next_piece);

  return cstate;
}

Piece *state_create_piece(State *state) {
  int spawnX = state->board->width / 2 - PIECE_SHAPE_WIDTH / 2;
  int spawnY = state->board->height + BOARD_HIDDEN - 1;

  Piece *pc = piece_create(
      piece_queue_get(state->piece_queue, state->piece_queue_index),
      spawnX,
      spawnY,
      ANGLE_UP
  );

  state->piece_queue_index++;

  return pc;
}

void state_next_piece(State *state) {
  assert(state != NULL);

  if (state->current_piece != NULL) {
    piece_free(state->current_piece);
    state->current_piece = NULL;
  }



  if (state->next_piece != NULL) {
    state->current_piece = state->next_piece;
    state->next_piece = NULL;
  } else {
    state->current_piece = state_create_piece(state);
  }

  if (state->next_piece != NULL) {
    piece_free(state->next_piece);
    state->next_piece = NULL;
  }

  state->next_piece = state_create_piece(state);

  motion_try_move(state->current_piece, state->board, 0, -1);
}

int state_step(State *state) {
  assert(state != NULL);

  state_add_step(state, 1);

  motion_try_move(state->current_piece, state->board, random_int(-1, 2), 0);
  motion_try_rotate(state->current_piece, state->board, (Rotation) random_int(-1, 2));

  if (!motion_try_move(state->current_piece, state->board, 0, -1)) {
    if (!board_merge_piece(state->board, state->current_piece))
      return 0;

    int hist[state->board->height];
    size_t count = board_get_completed_lines(state->board, hist);

    if (count) {
      state_add_broken_lines(state, (unsigned int) count);
      board_break_lines(state->board, hist);
    }

    state_next_piece(state);
  }

  return 1;
}