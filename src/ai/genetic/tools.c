//
// Created by dotty on 2/20/18.
//

#include "tools.h"

size_t board_height(const struct board *brd, size_t x)
{
  assert(brd != NULL);
  assert(x >= 0);
  assert(x < brd->width);

  size_t height = brd->height;

  for(size_t y = 0; y < brd->height && board_at(brd,x,y) == -1; ++y, --height)
  {}

  return height;
}

void board_heights(const struct board *brd, size_t *heights)
{
  assert(brd != NULL);
  assert(heights != NULL);

  for(size_t x = 0; x < brd->width; ++x)
  {
    heights[x] = board_height(brd,x);
  }
}

size_t bumpiness(const struct board *brd)
{
  assert(brd != NULL);

  size_t bumpiness = 0;
  size_t *heights = malloc(brd->width * sizeof(size_t));
  board_heights(brd, heights);

  for(size_t x = 0; x < brd->width - 1; ++x)
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
  for(size_t x = 0; x < brd->width; ++x)
  {
    agg_height += board_height(brd, x);
  }
  return agg_height;
};

size_t holes(const struct board *brd)
{
  //TODO
  //FIXME
  return 0;
}