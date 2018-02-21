/**
 * @file    board.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "board.h"

struct board *board_create(size_t width, size_t height) {
  assert(width > 0);
  assert(height > 0);

  struct board *brd = malloc(sizeof(struct board));
  memset(brd, 0, sizeof(struct board));

  brd->width = width;
  brd->height = height;

  brd->state = calloc(width * height, sizeof(int));

  //TODO change that to a memset please
  for (size_t y = 0; y < height; y++)
    for (size_t x = 0; x < width; x++)
      board_set(brd, x, y, -1);

  return brd;
}

void board_free(struct board *brd) {
  assert(brd != NULL);

  free(brd->state);
  free(brd);
}

int board_at(const struct board *brd, size_t x, size_t y) {
  assert(brd != NULL);
  assert(x >= 0);
  assert(y >= 0);
  assert(x < brd->width);
  assert(y < brd->height);

  return *(brd->state + y * brd->width + x);
}

void board_set(struct board *brd, size_t x, size_t y, int state) {
  assert(brd != NULL);
  assert(x >= 0);
  assert(y >= 0);
  assert(x < brd->width);
  assert(y < brd->height);

  *(brd->state + y * brd->width + x) = state;
}

void board_remove_line(struct board *brd, size_t line) {
  assert(brd != NULL);
  assert(line >= 0);
  assert(line < brd->height);

  for (size_t x = 0; x < brd->width; x++)
    board_set(brd, x, line, -1);
}

void board_move_line(struct board *brd, size_t src, size_t dest) {
  assert(brd != NULL);
  assert(src >= 0);
  assert(src < brd->height);
  assert(dest >= 0);
  assert(dest < brd->height);

  for (size_t x = 0; x < brd->width; x++) {
    board_set(brd, x, dest, board_at(brd, x, src));
    board_set(brd, x, src, -1);
  }
}

void board_print(const struct board *brd) {
  assert(brd != NULL);

  for (size_t y = 0; y < brd->height; y++) {
    for (size_t x = 0; x < brd->width; x++) {
      printf("%2d ", board_at(brd, x, y));
    }
    printf("\n");
  }
  printf("\n");
}

int board_is_line_complete(const struct board *brd, size_t line) {
  assert(brd != NULL);
  assert(line >= 0);
  assert(line < brd->height);

  for (size_t x = 0; x < brd->width; x++)
    if (board_at(brd, x, line) == -1)
      return 0;

  return 1;
}

size_t board_get_completed_lines(const struct board *brd, size_t **lines) {
  //TODO if lines == NULL just return number of lines please
  assert(brd != NULL);

  size_t count = 0;
  *lines = calloc(brd->height, sizeof(size_t));

  for (size_t y = 0; y < brd->height; y++) {
    if (board_is_line_complete(brd, y)) {
      (*lines)[count] = y;
      count++;
    }
  }

  return count;
}

void board_break_line(struct board *brd, size_t line) {
  assert(brd != NULL);
  assert(line >= 0);
  assert(line < brd->height);

  board_remove_line(brd, line);

  if (line == 0) return;

  for (size_t y = 0; y < line; y++) {
    size_t ry = line - 1 - y;
    board_move_line(brd, ry, ry + 1);
  }
}

void board_break_lines(struct board *brd, const size_t *lines, size_t llines) {
  assert(brd != NULL);
  assert(lines != NULL);
  if (llines == 0) return;

  for (size_t i = 0; i < llines; i++)
    board_break_line(brd, lines[i]);
}