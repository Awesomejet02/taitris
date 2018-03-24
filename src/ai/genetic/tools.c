/**
 * @file    tools.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Tools for the genetic algorithm
 */

#include "tools.h"
#include "../../engine/state.h"
#include "../../engine/board.h"

//TODO
//FIXME use state_at foncions

void board_heights(const State *state, int *heights)
{
  assert(state != NULL);
  assert(heights != NULL);

  for(int x = 0; x < state->board->width; ++x)
  {
    heights[x] = board_height(state,x);
  }
}

int board_height(const State *state, int x)
{
  assert(state != NULL);
  assert(x < state->board->width);

  int height = state->board->height - 1;

  for(; height >= 0 && state_at(state, x, height) == CELL_EMPTY; --height);

  return height + 1;
}

int bumpiness(const State *state)
{
  assert(state != NULL);

  int bumpiness = 0;
  int *heights = malloc(state->board->width * sizeof(int));
  board_heights(state, heights);

  for(int x = 0; x < state->board->width - 1; ++x)
  {
    int diff = heights[x] - heights[x + 1]; //TODO fix the ABS macro but not mandatory
    bumpiness += ABS(diff);
  }

  free(heights);
  return bumpiness;
}

int aggregate_height(const State *state)
{
  assert(state != NULL);

  int agg_height = 0;
  for(int x = 0; x < state->board->width; ++x)
  {
    agg_height += board_height(state, x);
  }
  return agg_height;
}

int hole(const State *state, int x)
{
  assert(state != NULL);
  assert(x < state->board->width);

  int h = board_height(state, x);
  if (h == 0)
    return 0;

  int holes = 0;
  int y = 0;
  while(y < h)
  {
    if(state_at(state, x, y) == CELL_EMPTY)
    {
      ++holes;
    }
    ++y;
  }

  return holes;
}

int holes(const State *state)
{
  assert(state != NULL);

  int holes = 0;
  for(int x = 0; x < state->board->width; ++x)
  {
    holes += hole(state, x);
  }

  return holes;
}

int clears(const State *state)
{
  assert(state != NULL);

  int count = 0;

  for (int y = 0; y < state->board->height; y++) {
    int is_complete = 1;
    for (int x = 0; x < state->board->width; x++)
      if(state_at(state, x, y) == CELL_EMPTY)
      {
        is_complete = 0;
        break;
      }
    count += is_complete;
  }
  return count;
}

void show_features(const State *state)
{
  assert(state != NULL);

  printf("holes: " ANSI_FG_GREEN "%d\n" ANSI_RESET, holes(state));
  printf("aggregate_height: " ANSI_FG_GREEN "%d\n" ANSI_RESET , aggregate_height(state));
  printf("clears: " ANSI_FG_GREEN "%d\n" ANSI_RESET, clears(state));
  printf("bumpiness: " ANSI_FG_GREEN "%d\n" ANSI_RESET, bumpiness(state));
}
