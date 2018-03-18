/**
 * @file    score.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Scoring system
 */
#ifndef TAITRIS_SCORE_H
#define TAITRIS_SCORE_H

#include <stdlib.h>
#include <assert.h>

#define SCORE_SINGLE 100
#define SCORE_DOUBLE 300
#define SCORE_TRIPLE 500
#define SCORE_TETRIS 800

#define SCORE_SDROP 1
#define SCORE_HDROP 2

#define SCORE_LVL_PER_LINE 10

static inline
unsigned int score_get(int combo, unsigned int level) {
  switch (combo) {
    case 1:
      return SCORE_SINGLE * level;
    case 2:
      return SCORE_DOUBLE * level;
    case 3:
      return SCORE_TRIPLE * level;
    case 4:
      return SCORE_TETRIS * level;
    default:
      return 0;
  }
}

unsigned int score_compute_break(const int hist[], size_t len,
                                 unsigned int level);

#endif //TAITRIS_SCORE_H
