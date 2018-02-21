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
#include <assert.h>
#include <string.h>
#include <err.h>

#include "piece.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 22
#define BOARD_CELL_EMPTY (-1)

struct board {
  int data[BOARD_HEIGHT][BOARD_WIDTH];
};

struct board *board_create();
void board_init(struct board *brd);
void board_free(struct board *brd);
struct board *board_copy(const struct board *brd);
int board_at(const struct board *brd, size_t x, size_t y);
void board_set(struct board *brd, size_t x, size_t y, int state);
void board_remove_line(struct board *brd, size_t line);
void board_move_line(struct board *brd, size_t src, size_t dest);
int board_is_line_complete(const struct board *brd, size_t line);
size_t board_get_completed_lines(const struct board *brd, size_t **lines);
void board_break_line(struct board *brd, size_t line);
void board_break_lines(struct board *brd, const size_t *lines, size_t llines);
void board_merge_piece(struct board *brd, struct piece pc);
int board_check_position(const struct board *brd, struct piece pc);
void board_print(const struct board *brd);

#endif //TAITRIS_BOARD_H