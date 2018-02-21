/**
 * @file    board.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#ifndef TAITRIS_BOARD_H
#define TAITRIS_BOARD_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "piece.h"

#define BOARD_CELL_EMPTY (-1)
#define BOARD_CELL_CYAN 0
#define BOARD_CELL_YELLOW 1
#define BOARD_CELL_PURPLE 2
#define BOARD_CELL_ORANGE 3
#define BOARD_CELL_BLUE 4
#define BOARD_CELL_RED 5
#define BOARD_CELL_GREEN 6

struct board {
  size_t width;
  size_t height;

  int *data;
};

extern inline
struct board *board_create(size_t width, size_t height);

extern inline
void board_init(struct board *brd);

extern inline
void board_free(struct board *brd);

extern inline
struct board *board_copy(const struct board *brd);

extern inline
int board_at(const struct board *brd, size_t x, size_t y);

extern inline
void board_set(struct board *brd, size_t x, size_t y, int state);

extern inline
void board_remove_line(struct board *brd, size_t line);

extern inline
void board_move_line(struct board *brd, size_t src, size_t dest);

extern inline
void board_print(const struct board *brd);

extern inline
int board_is_line_complete(const struct board *brd, size_t line);

extern inline
size_t board_get_completed_lines(const struct board *brd, size_t **lines);

extern inline
void board_break_line(struct board *brd, size_t line);

extern inline
void board_break_lines(struct board *brd, const size_t *lines, size_t llines);

extern inline
void board_merge_piece(struct board *brd, struct piece pc);

extern inline
int board_check_position(const struct board *brd, struct piece pc);

#endif //TAITRIS_BOARD_H
