/**
 * @file    game.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#ifndef TAITRIS_GAME_H
#define TAITRIS_GAME_H

#include <stdlib.h>
#include <err.h>

typedef struct shape {
  size_t h;
  size_t w;

  int *form;
} shape;

typedef struct piece {
  size_t id;

  size_t x;
  size_t y;

  size_t c_i;

  size_t n;
  shape **shapes_;
} piece;

typedef struct board {
  size_t h;
  size_t w;

  size_t lvl;

  size_t score;

  int *board_;

  piece *piece_;
} board;

board *init_board(size_t h, size_t w, size_t lvl);
void free_board(board *board_);
int loose(board *board_, piece *piece);
int isLineFull(board *board_, size_t y);
void removeLine(board *board_, size_t y);

piece *init_piece(size_t id, size_t x);
int checkPosition(board *board_, piece *piece_);
int fixPosition(board *board_, piece *piece_);

void createShape(shape *shape, size_t w, size_t h, const int data[]);
shape **getShape(size_t id, size_t *n);

#endif //TAITRIS_GAME_H
