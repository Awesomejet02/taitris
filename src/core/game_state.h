/**
 * @file    game_state.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#ifndef TAITRIS_GAME_STATE_H
#define TAITRIS_GAME_STATE_H

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "board.h"

#define GS_STATE_PAUSED 0
#define GS_STATE_PLAYING 1
#define GS_STATE_GAMEOVER 2

struct game_state {
  int level;
  int score;

  int broken_lines;

  int state;

  time_t game_start;
  time_t pause_start;

  struct board *board;
};

extern inline
struct game_state *gs_create(size_t brd_width, size_t brd_height);

extern inline
void gs_init(struct game_state *gs);

extern inline
void gs_free(struct game_state *gs);

extern inline
void gs_set_state(struct game_state *gs, int state);

extern inline
time_t gs_current_time();

extern inline
time_t gs_elapsed_time(const struct game_state *gs);

#endif //TAITRIS_GAME_STATE_H
