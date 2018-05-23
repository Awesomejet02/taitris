/**
 * @file    tools.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Tools for the genetic algorithm
 */

#include "tools.h"
#include "../../engine/piece/piece.h"

int genetic_tools_height(const State *state, int x)
{
  assert(state != NULL);
  assert(x < state->board->width);

  int height = state->board->height - 1;

  for(; height >= 0 && state_at(state, x, height) == CELL_EMPTY; --height);

  return height + 1;
}

void genetic_tools_heights(const State *state, int *heights)
{
  assert(state != NULL);
  assert(heights != NULL);

  for(int x = 0; x < state->board->width; ++x)
    heights[x] = genetic_tools_height(state, x);
}

int genetic_tools_bumpiness(const State *state)
{
  assert(state != NULL);

  int bumpiness = 0;
  int *heights = malloc(state->board->width * sizeof(int));
  genetic_tools_heights(state, heights);

  for(int x = 0; x < state->board->width - 1; ++x)
  {
    int diff = heights[x] - heights[x + 1];
    //TODO fix the TOOLS_ABS macro but not mandatory
    bumpiness += TOOLS_ABS(diff);
  }

  free(heights);
  return bumpiness;
}

int genetic_tools_aggregate_height(const State *state)
{
  assert(state != NULL);

  int agg_height = 0;

  for(int x = 0; x < state->board->width; ++x)
    agg_height += genetic_tools_height(state, x);

  return agg_height;
}

int genetic_tools_hole(const State *state, int x)
{
  assert(state != NULL);
  assert(x < state->board->width);

  int h = genetic_tools_height(state, x);
  if (h == 0) return 0;

  int holes = 0;
  int y = 0;

  while(y < h)
  {
    if(state_at(state, x, y) == CELL_EMPTY)
      ++holes;

    ++y;
  }

  return holes;
}

int genetic_tools_holes(const State *state)
{
  assert(state != NULL);

  int holes = 0;

  for(int x = 0; x < state->board->width; ++x)
    holes += genetic_tools_hole(state, x);

  return holes;
}

int genetic_tools_clears(const State *state)
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

Input delta_piece(const Piece *current, const Piece *target)
{
  assert(current != NULL);
  assert(target != NULL);
  if (current->angle != target->angle){
    return INPUT_ROTATE_RIGHT;
  } else if (current->x > target->x){
    return INPUT_MOVE_LEFT;
  } else if (current->x < target->x){
    return INPUT_MOVE_RIGHT;
  } else {
    return INPUT_EMPTY;
  }
}