/**
 * @file    tools.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Tools for the genetic algorithm
 */

#include "tools.h"

void board_heights(const Board *brd, int *heights)
{
  assert(brd != NULL);
  assert(heights != NULL);

  for(int x = 0; x < brd->width; ++x)
  {
    heights[x] = board_height(brd,x);
  }
}

int board_height(const Board *brd, int x)
{
  assert(brd != NULL);
  assert(x < brd->width);

  int height = brd->height - 1;

  for(; height >= 0 && board_at(brd, x, height) == CELL_EMPTY; --height);

  return height + 1;
}

int bumpiness(const Board *brd)
{
  assert(brd != NULL);

  int bumpiness = 0;
  int *heights = malloc(brd->width * sizeof(int));
  board_heights(brd, heights);

  for(int x = 0; x < brd->width - 1; ++x)
  {
    int diff = heights[x] - heights[x + 1]; //TODO fix the ABS macro but not mandatory
    bumpiness += ABS(diff);
  }

  free(heights);
  return bumpiness;
}

int aggregate_height(const Board *brd)
{
  assert(brd != NULL);

  int agg_height = 0;
  for(int x = 0; x < brd->width; ++x)
  {
    agg_height += board_height(brd, x);
  }
  return agg_height;
}

int hole(const Board *brd, int x)
{
  int h = board_height(brd, x);
  if (h == 0)
    return 0;

  int holes = 0;
  int y = 0;
  while(y < h)
  {
    if(board_at(brd, x, y) == CELL_EMPTY)
    {
      ++holes;
    }
    ++y;
  }

  return holes;
}

int holes(const Board *brd)
{
  int holes = 0;
  for(int x = 0; x < brd->width; ++x)
  {
    holes += hole(brd, x);
  }

  return holes;
}

int clears(const Board *brd)
{
  size_t c = board_get_completed_lines(brd, NULL);
  return c;
}

void show_features(const Board *brd)
{
  printf("holes: " ANSI_FG_GREEN "%d\n" ANSI_RESET, holes(brd));
  printf("aggregate_height: " ANSI_FG_GREEN "%d\n" ANSI_RESET , aggregate_height(brd));
  printf("clears: " ANSI_FG_GREEN "%d\n" ANSI_RESET, clears(brd));
  printf("bumpiness: " ANSI_FG_GREEN "%d\n" ANSI_RESET, bumpiness(brd));
}
