/**
 * @file    piece.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Piece
 */
#ifndef TAITRIS_PIECE_H
#define TAITRIS_PIECE_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <err.h>

#include "piece_type.h"
#include "piece_shape.h"
#include "../angle.h"
#include "../../utils/random.h"

typedef struct {
  PieceType type;
  const PieceShape *shape;
  int x;
  int y;
  Angle angle;
} Piece;

static inline
void piece_move(Piece *pc, int dx, int dy) {
  assert(pc != NULL);

  pc->x += dx;
  pc->y += dy;
}

static inline
void piece_rotate(Piece *pc, Rotation rotation) {
  assert(pc != NULL);

  pc->angle = angle_rotate(pc->angle, rotation);
}

Piece *piece_create(PieceType type, int x, int y, Angle angle);
void piece_free(Piece *pc);
Piece *piece_copy(const Piece *pc);
Piece *piece_random(int x, int y, Angle angle);

#endif //TAITRIS_PIECE_H
