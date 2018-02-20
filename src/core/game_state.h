/**
 * @file    game_state.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#ifndef TAITRIS_GAME_STATE_H
#define TAITRIS_GAME_STATE_H

#include <time.h>

struct game_state {
  int level;
  int score;
  int broken_lines;
  struct timespec start_time;
};

#endif //TAITRIS_GAME_STATE_H
