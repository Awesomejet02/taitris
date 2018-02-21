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

  brd->data = malloc(width * height * sizeof(int));
  board_init(brd);

  return brd;
}

void board_init(struct board *brd) {
  assert(brd != NULL);

  memset(brd->data, BOARD_CELL_EMPTY, brd->width * brd->height * sizeof(int));
}

void board_free(struct board *brd) {
  assert(brd != NULL);

  free(brd->data);
  free(brd);
}

struct board *board_copy(const struct board *brd) {
  assert(brd != NULL);

  struct board *bcp = board_create(brd->width, brd->height);
  memcpy(bcp->data, brd->data, brd->width * brd->height * sizeof(int));

  return bcp;
}

int board_at(const struct board *brd, size_t x, size_t y) {
  assert(brd != NULL);
  assert(x >= 0);
  assert(y >= 0);
  assert(x < brd->width);
  assert(y < brd->height);

  return *(brd->data + y * brd->width + x);
}

void board_set(struct board *brd, size_t x, size_t y, int state) {
  assert(brd != NULL);
  assert(x >= 0);
  assert(y >= 0);
  assert(x < brd->width);
  assert(y < brd->height);
  assert(state >= -1);
  assert(state < 7);

  *(brd->data + y * brd->width + x) = state;
}

void board_remove_line(struct board *brd, size_t line) {
  assert(brd != NULL);
  assert(line >= 0);
  assert(line < brd->height);

  for (size_t x = 0; x < brd->width; x++)
    board_set(brd, x, line, BOARD_CELL_EMPTY);
}

void board_move_line(struct board *brd, size_t src, size_t dest) {
  assert(brd != NULL);
  assert(src >= 0);
  assert(src < brd->height);
  assert(dest >= 0);
  assert(dest < brd->height);

  for (size_t x = 0; x < brd->width; x++) {
    board_set(brd, x, dest, board_at(brd, x, src));
    board_set(brd, x, src, BOARD_CELL_EMPTY);
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
    if (board_at(brd, x, line) == BOARD_CELL_EMPTY)
      return 0;

  return 1;
}

size_t board_get_completed_lines(const struct board *brd, size_t **lines) {
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

void board_merge_piece(struct board *brd, struct piece pc) {
  assert(brd != NULL);

  for (size_t i = 0; i < PIECE_HEIGHT; i++)
    for (size_t j = 0; j < PIECE_WIDTH; j++)
      if (pc.shapes[pc.angle][i][j] > 0)
        board_set(brd, pc.x + j, pc.y + i, (int) pc.id);
}

int board_check_position(const struct board *brd, struct piece pc) {
  assert(brd != NULL);

  for (size_t i = 0; i < PIECE_HEIGHT; i++) {
    for (size_t j = 0; j < PIECE_WIDTH; j++) {
      size_t y = pc.y + i;
      size_t x = pc.x + j;

      if (x < 0 || x >= brd->width || y < 0 || y >= brd->height) return 0;

      if (pc.shapes[pc.angle][i][j] > 0 &&
          board_at(brd, x, y) != BOARD_CELL_EMPTY) return 0;
    }
  }
  
  return 1;
}