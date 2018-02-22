//
// Created by dotty on 2/20/18.
//

#include "tools.h"

void board_heights(const struct board *brd, size_t *heights)
{
  assert(brd != NULL);
  assert(heights != NULL);

  for(size_t x = 0; x < BOARD_WIDTH; ++x)
  {
    heights[x] = board_height(brd,x);
  }
}

size_t board_height(const struct board *brd, size_t x)
{
  assert(brd != NULL);
  assert(x < BOARD_WIDTH);

  size_t height = BOARD_HEIGHT;

  for(size_t y = 0; y < BOARD_HEIGHT && board_at(brd,x,y) == -1; ++y, --height)
  {}

  return height;
}

size_t bumpiness(const struct board *brd)
{
  assert(brd != NULL);

  size_t bumpiness = 0;
  size_t *heights = malloc(BOARD_WIDTH * sizeof(size_t));
  board_heights(brd, heights);

  for(size_t x = 0; x < BOARD_WIDTH - 1; ++x)
  {
    int diff = heights[x] - heights[x + 1]; //TODO fix the ABS macro but not mandatory
    bumpiness += ABS(diff);
  }

  free(heights);
  return bumpiness;
}

size_t aggregate_height(const struct board *brd)
{
  assert(brd != NULL);

  size_t agg_height = 0;
  for(size_t x = 0; x < BOARD_WIDTH; ++x)
  {
    agg_height += board_height(brd, x);
  }
  return agg_height;
}

size_t hole(const struct board *brd, size_t x)
{
  size_t h = board_height(brd, x);
  if (h == 0)
    return 0;

  size_t holes = 0;
  h = BOARD_HEIGHT - h; //point to board cell
  while(h < BOARD_HEIGHT)
  {
    if(board_at(brd, x, h) == BOARD_CELL_EMPTY)
    {
      ++holes;
      while(h + 1 < BOARD_HEIGHT && board_at(brd, x, h + 1) == BOARD_CELL_EMPTY)
      {
        ++h;
      }
    }
    ++h; //go down
  }

  return holes;
}

size_t holes(const struct board *brd)
{
  size_t holes = 0;
  for(size_t x = 0; x < BOARD_WIDTH; ++x)
  {
    holes += hole(brd, x);
  }

  return holes;
}

void make_line(struct board *brd, size_t y)
{
  for(size_t x = 0; x < BOARD_WIDTH; ++x)
  {
    board_set(brd, x, y, 42);
  }
}

size_t clears(const struct board *brd)
{
  size_t *lines;
  size_t c = board_get_completed_lines(brd, &lines);
  return c;
}
