/**
 * @file    board.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Board
 */
#include "board.h"

Board *board_create(int width, int height) {
  assert(width > 0);
  assert(height > 0);

  Board *brd = malloc(sizeof(Board));

  if (brd == NULL)
    errx(EXIT_FAILURE, "Can't initialize board object");

  memset(brd, 0, sizeof(Board));

  brd->width = width;
  brd->height = height;

  brd->cells = malloc(sizeof(Cell) * height * width);

  if (brd->cells == NULL)
    errx(EXIT_FAILURE, "Can't initialize board of size %d x %d", width, height);

  return brd;
}

void board_init(Board *brd) {
  assert(brd != NULL);

  memset(brd->cells, 0, sizeof(Cell) * brd->height * brd->width);
}

void board_free(Board *brd) {
  assert(brd != NULL);

  free(brd->cells);
  free(brd);
}

Board *board_copy(Board *brd) {
  assert(brd != NULL);

  Board *cbrd = board_create(brd->width, brd->height);

  memcpy(cbrd->cells, brd->cells, sizeof(Cell) * cbrd->height * cbrd->width);

  return cbrd;
}

size_t board_get_completed_lines(const Board *brd, int *hist) {
  assert(brd != NULL);

  size_t count = 0;

  for (int y = 0; y < brd->height; y++) {
    if (board_is_line_complete(brd, y)) {
      if (hist) hist[y] = 1;
      count++;
    } else if (hist) {
      hist[y] = 0;
    }
  }

  return count;
}

void board_break_lines(Board *brd, const int *hist) {
  assert(brd != NULL);
  assert(hist != NULL);

  int delta = 0;

  int y;
  for (y = board_reverse_y(brd, 0); y >= 0; y--) {
    if (hist[y]) {
      delta++;
    } else {
      if (delta)
        board_down_lines(brd, y + delta + 1, delta);

      delta = 0;
    }
  }

  if (delta)
    board_down_lines(brd, y + delta + 1, delta);
}