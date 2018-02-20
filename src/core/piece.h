/**
 * @file    piece.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#ifndef TAITRIS_PIECE_H
#define TAITRIS_PIECE_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define PIECE_I 0
#define PIECE_O 1
#define PIECE_T 2
#define PIECE_L 3
#define PIECE_J 4
#define PIECE_Z 5
#define PIECE_S 6

#define PIECE_ANGLE_UP 0
#define PIECE_ANGLE_RIGHT 1
#define PIECE_ANGLE_BOTTOM 2
#define PIECE_ANGLE_LEFT 3

#define PIECE_ROTATE_LEFT -1;
#define PIECE_ROTATE_RIGHT 1;

struct piece {
  size_t id;

  size_t x;
  size_t y;

  size_t width;
  size_t height;

  size_t angle;

  int shape[6];
};

struct piece *piece_create(size_t id, size_t x, size_t y);

extern inline
void piece_free(struct piece *pc);

void piece_rotate(struct piece *pc, int rotation);

extern inline
void piece_move(struct piece *pc, int dx, int dy);

#endif //TAITRIS_PIECE_H
