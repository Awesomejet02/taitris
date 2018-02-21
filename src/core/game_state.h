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
#include <assert.h>

#include "board.h"
#include "piece.h"

#define GS_STATE_PAUSED 0
#define GS_STATE_PLAYING 1
#define GS_STATE_GAMEOVER 2

struct game_state {
  int level;
  int score;

  int broken_lines;

  int state;

  double time;

  struct piece piece_current;
  struct piece piece_next;

  struct board *board;
};

extern inline
struct game_state *gs_create();

extern inline
void gs_init(struct game_state *gs);

extern inline
void gs_free(struct game_state *gs);

extern inline
void gs_next_piece(struct game_state *gs);

#endif //TAITRIS_GAME_STATE_H
