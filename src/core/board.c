/**
 * @file    board.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "board.h"

struct board *board_create() {
  struct board *brd = malloc(sizeof(struct board));

  if(!brd)
    errx(EXIT_FAILURE, "Can't initialize board of size %d x %d",
         BOARD_WIDTH,
         BOARD_HEIGHT);

  return brd;
}

void board_init(struct board *brd) {
  assert(brd != NULL);

  memset(brd, -1, sizeof(struct board));
}

void board_free(struct board *brd) {
  assert(brd != NULL);

  free(brd);
}

struct board *board_copy(const struct board *brd) {
  assert(brd != NULL);

  struct board *cbrd = board_create();
  memcpy(cbrd, brd, sizeof(struct board));

  return cbrd;
}

int board_at(const struct board *brd, size_t x, size_t y) {
  assert(brd != NULL);
  assert(x < BOARD_WIDTH);
  assert(y < BOARD_HEIGHT);

  return brd->data[y][x];
}

void board_set(struct board *brd, size_t x, size_t y, int state) {
  assert(brd != NULL);
  assert(x < BOARD_WIDTH);
  assert(y < BOARD_HEIGHT);

  brd->data[y][x] = state;
}

void board_remove_line(struct board *brd, size_t line) {
  assert(brd != NULL);
  assert(line < BOARD_HEIGHT);

  for (size_t x = 0; x < BOARD_WIDTH; x++)
    board_set(brd, x, line, BOARD_CELL_EMPTY);
}


void board_move_line(struct board *brd, size_t src, size_t dest) {
  assert(brd != NULL);
  assert(src < BOARD_HEIGHT);
  assert(dest < BOARD_HEIGHT);

  for (size_t x = 0; x < BOARD_WIDTH; x++) {
    board_set(brd, x, dest, board_at(brd, x, src));
    board_set(brd, x, src, BOARD_CELL_EMPTY);
  }
}

int board_is_line_complete(const struct board *brd, size_t line) {
  assert(brd != NULL);
  assert(line < BOARD_HEIGHT);

  for (size_t x = 0; x < BOARD_WIDTH; x++)
    if (board_at(brd, x, line) == BOARD_CELL_EMPTY)
      return 0;

  return 1;
}

size_t board_get_completed_lines(const struct board *brd, size_t **lines) {
  assert(brd != NULL);

  size_t count = 0;

  if (lines != NULL)
    *lines = calloc(BOARD_HEIGHT, sizeof(size_t));

  for (size_t y = 0; y < BOARD_HEIGHT; y++) {
    if (board_is_line_complete(brd, y)) {
      if (lines != NULL)
        (*lines)[count] = y;

      count++;
    }
  }

  return count;
}

void board_break_line(struct board *brd, size_t line) {
  assert(brd != NULL);
  assert(line < BOARD_HEIGHT);

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

      if (x >= BOARD_WIDTH || y >= BOARD_HEIGHT) return 0;

      if (pc.shapes[pc.angle][i][j] > 0 &&
          board_at(brd, x, y) != BOARD_CELL_EMPTY) return 0;
    }
  }

  return 1;
}

void board_print(const struct board *brd) {
  assert(brd != NULL);

  for (size_t y = 0; y < BOARD_HEIGHT; y++) {
    for (size_t x = 0; x < BOARD_WIDTH; x++)
      printf("%2d ", board_at(brd, x, y));

    printf("\n");
  }
  printf("\n");
}