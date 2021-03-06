/**
 * @file    piece.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Piece
 */
#include "piece.h"

Piece *piece_create(PieceType type, int x, int y, Angle angle) {
  Piece *pc = malloc(sizeof(Piece));

  if (pc == NULL)
    errx(EXIT_FAILURE, "Can't create piece type %d at %dx%d", type, x, y);

  memset(pc, 0, sizeof(Piece));

  pc->type = type;
  pc->shape = piece_shape(type);
  pc->x = x;
  pc->y = y;
  pc->angle = angle;

  return pc;
}

void piece_free(Piece *pc) {
  assert(pc != NULL);

  free(pc);
}

Piece *piece_copy(const Piece *pc) {
  assert(pc != NULL);

  Piece *cpc = malloc(sizeof(Piece));

  if (cpc == NULL)
    errx(EXIT_FAILURE, "Can't copy piece");

  piece_set(cpc, pc);

  return cpc;
}

Piece *piece_random(int x, int y, Angle angle) {
  return piece_create(seven_bag_draw(), x, y, angle);
}