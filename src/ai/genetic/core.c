/**
 * @file    core.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Core of the genetic algorithm
 */

#include "core.h"

void genetic_show_stats(State *state)
{
  assert(state != NULL);

  show_features(state->board);
  printf("Rank: " ANSI_FG_RED "%f\n\n" ANSI_RESET, get_rank(state));
}