/**
 * @file    board.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Board
 */
#ifndef TAITRIS_BOARD_H
#define TAITRIS_BOARD_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <err.h>

#include "piece/piece.h"
#include "cell.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define BOARD_HIDDEN 2

typedef struct {
  int width;
  int height;

  Cell *cells;
} Board;

#define board_reverse_y(_brd_, _y_) \
  ((_brd_)->height - 1 - (_y_))

static inline
Cell board_at(const Board *brd, int x, int y) {
  assert(brd != NULL);
  assert(x >= 0);
  assert(x < brd->width);
  assert(y >= 0);
  assert(y < brd->height);

  return *(brd->cells + board_reverse_y(brd, y) * brd->width + x);
}

static inline
void board_set(Board *brd, int x, int y, Cell cell) {
  assert(brd != NULL);
  assert(x >= 0);
  assert(x < brd->width);
  assert(y >= 0);
  assert(y < brd->height);

  *(brd->cells + board_reverse_y(brd, y) * brd->width + x) = cell;
}

static inline
void board_down_lines(Board *brd, int line, int delta) {
  assert(brd != NULL);
  assert(line > 0);
  assert(line <= brd->height);
  assert(delta > 0);
  assert((line - delta) >= 0);

  if (line < brd->height)
    memcpy(brd->cells + delta * brd->width,
           brd->cells,
           sizeof(Cell) * brd->width * (brd->height - line));

  memset(brd->cells, 0, sizeof(Cell) * brd->width * delta);
}

static inline
int board_is_line_complete(const Board *brd, int line) {
  assert(brd != NULL);
  assert(line >= 0);
  assert(line < brd->height);

  for (int x = 0; x < brd->width; x++)
    if(board_at(brd, x, line) == CELL_EMPTY)
      return 0;

  return 1;
}

Board *board_create(int width, int height);

void board_init(Board *brd);

void board_free(Board *brd);

Board *board_copy(Board *brd);

size_t board_get_completed_lines(const Board *brd, int *hist);

void board_break_lines(Board *brd, const int *hist);

int board_merge_piece(Board *brd, const Piece *pc);

#endif //TAITRIS_BOARD_H
