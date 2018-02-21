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

#include "../utils/random.h"
#include "board.h"

#define PIECE_I 0
#define PIECE_O 1
#define PIECE_T 2
#define PIECE_L 3
#define PIECE_J 4
#define PIECE_Z 5
#define PIECE_S 6
#define PIECE_COUNT 7

#define PIECE_WIDTH 4
#define PIECE_HEIGHT 4

#define PIECE_ANGLE_UP 0
#define PIECE_ANGLE_RIGHT 1
#define PIECE_ANGLE_DOWN 2
#define PIECE_ANGLE_LEFT 3
#define PIECE_ANGLES 4

#define PIECE_ROTATE_LEFT (-1)
#define PIECE_ROTATE_RIGHT 1

const int PIECE_SHAPES[PIECE_COUNT][PIECE_ANGLES][PIECE_HEIGHT][PIECE_WIDTH];

struct piece {
  size_t id;

  size_t x;
  size_t y;

  size_t angle;

  int shapes[PIECE_ANGLES][PIECE_HEIGHT][PIECE_WIDTH];
};

void piece_random(struct piece *pc, size_t x, size_t y, int first);

void piece_move(struct piece *pc, int dx, int dy);
int piece_can_move(struct piece pc, const struct board *brd, int dx, int dy);
int piece_try_move(struct piece *pc, const struct board *brd, int dx, int dy);

void piece_rotate(struct piece *pc, int rotation);
int piece_can_rotate(struct piece pc, const struct board *brd, int rotation);
int piece_try_rotate(struct piece *pc, const struct board *brd, int rotation);

#endif //TAITRIS_PIECE_H
