//
// Created by dotty on 3/17/18.
//

#include "core.h"

void genetic_show_stats(State *state)
{
  assert(state != NULL);

  show_features(state->board);
  printf("Rank: " ANSI_FG_RED "%f\n" ANSI_RESET, get_rank(state));
}