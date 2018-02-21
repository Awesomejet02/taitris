/**
 * @file    game_state.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "game_state.h"

struct game_state *gs_create() {
  struct game_state *gs = malloc(sizeof(struct game_state));
  memset(gs, 0, sizeof(struct game_state));

  gs->board = board_create();

  return gs;
}

void gs_init(struct game_state *gs) {
  assert(gs != NULL);

  gs->level = 1;
  gs->score = 0;
  gs->broken_lines = 0;
  gs->state = GS_STATE_PLAYING;

  gs->time = 0;

  board_init(gs->board);

  piece_random(&gs->piece_next, GS_SPAWN_X, GS_SPAWN_Y);

  gs_next_piece(gs);
}

void gs_free(struct game_state *gs) {
  assert(gs != NULL);

  board_free(gs->board);
  free(gs);
}

int gs_next_piece(struct game_state *gs) {
  memcpy(&gs->piece_current, &gs->piece_next, sizeof(struct piece));
  piece_random(&gs->piece_next, GS_SPAWN_X, GS_SPAWN_Y);

  return board_check_position(gs->board, gs->piece_current);
}