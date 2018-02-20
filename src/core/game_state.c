/**
 * @file    game_state.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "game_state.h"

struct game_state *gs_create(size_t brd_width, size_t brd_height) {
  assert(brd_width > 0);
  assert(brd_height > 0);

  struct game_state *gs = malloc(sizeof(struct game_state));
  memset(gs, 0, sizeof(struct game_state));

  gs->board = board_create(brd_width, brd_height);

  return gs;
}

void gs_init(struct game_state *gs) {
  assert(gs != NULL);

  gs->level = 1;
  gs->score = 0;
  gs->broken_lines = 0;
  gs->state = GS_STATE_PLAYING;

  gs->game_start = gs_current_time();
  gs->pause_start = 0;

  board_init(gs->board);
}

void gs_free(struct game_state *gs) {
  assert(gs != NULL);

  board_free(gs->board);
  free(gs);
}

void gs_set_state(struct game_state *gs, int state) {
  assert(gs != NULL);

  if (gs->state == GS_STATE_PLAYING && state == GS_STATE_PAUSED)
    gs->pause_start = gs_current_time();

  if (gs->state == GS_STATE_PAUSED && state == GS_STATE_PLAYING) {
    gs->game_start += gs_current_time() - gs->pause_start;
    gs->pause_start = 0;
  }

  gs->state = state;
}

time_t gs_current_time() {
  struct timespec curr;
  clock_gettime(CLOCK_MONOTONIC, &curr);
  return curr.tv_sec;
}

time_t gs_elapsed_time(const struct game_state *gs) {
  assert(gs != NULL);

  return gs_current_time() - gs->game_start;
}

// TODO: Faire les pièces
// TODO: Game loop
// TODO: Random
// TODO: Pièce vers le board
// TODO: Rotation des pièces
// TODO: Déplacement des pièces
