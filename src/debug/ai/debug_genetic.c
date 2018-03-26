/**
 * @file    debug_genetic.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Genetic algorithm debuging
 */
#include "debug_genetic.h"

void debug_genetic_print_stats(const State *state) {
  printf(DEBUG_STATE_TAG "Printing features ");

  if (state == NULL) {
    printf(ANSI_BOLD ANSI_FG_RED "NULL" ANSI_RESET "\n");
    return;
  }
  else {
    printf(ANSI_BOLD "%p" ANSI_RESET "\n", state);
  }

  printf("\n");

  printf("Holes: " ANSI_FG_GREEN "%d\n" ANSI_RESET,
         genetic_tools_holes(state));

  printf("Aggregate_height: " ANSI_FG_GREEN "%d\n" ANSI_RESET ,
         genetic_tools_aggregate_height(state));

  printf("Clears: " ANSI_FG_GREEN "%d\n" ANSI_RESET,
         genetic_tools_clears(state));

  printf("Bumpiness: " ANSI_FG_GREEN "%d\n" ANSI_RESET,
         genetic_tools_bumpiness(state));

  printf("---------\n");

  printf("Rank: " ANSI_FG_RED "%f\n\n" ANSI_RESET, genetic_get_rank(state));
}