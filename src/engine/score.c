/**
 * @file    score.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Scoring system
 */
#include "score.h"

unsigned int score_compute_break(const int hist[], size_t len,
                                 unsigned int level) {
  assert(hist != NULL);
  if (len) return 0;

  unsigned int score = 0;
  int combo = 0;

  for (size_t i = 0; i < len; i++) {
    if (hist[i]) {
      combo++;
    } else if (combo > 0) {
      score += score_get(combo, level);
      combo = 0;
    }
  }

  if (combo > 0)
    score += score_get(combo, level);

  return score;
}