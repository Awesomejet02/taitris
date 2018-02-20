/**
 * @file    piece.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "piece.h"

struct piece *piece_create(size_t id, size_t x, size_t y) {
  struct piece *pc = malloc(sizeof(struct piece));
  memset(pc, 0, sizeof(struct piece));

  pc->id = id;
  pc->x = x;
  pc->y = y;
  pc->angle = PIECE_ANGLE_UP;

  if (id == PIECE_I) {
    pc->width = 4;
    pc->height = 1;
  } else if (id == PIECE_O) {
    pc->width = 2;
    pc->height = 2;
  } else {
    pc->width = 3;
    pc->height = 2;
  }

  switch (id) {
    case PIECE_I:
      pc->shape[0] =  0;
      pc->shape[1] =  0;
      pc->shape[2] =  0;
      pc->shape[3] =  0;
      pc->shape[4] = -1;
      pc->shape[5] = -1;
      break;
    case PIECE_O:
      pc->shape[0] =  1;
      pc->shape[1] =  1;
      pc->shape[2] =  1;
      pc->shape[3] =  1;
      pc->shape[4] = -1;
      pc->shape[5] = -1;
      break;
    case PIECE_T:
      pc->shape[0] =  2;
      pc->shape[1] =  2;
      pc->shape[2] =  2;
      pc->shape[3] = -1;
      pc->shape[4] =  2;
      pc->shape[5] = -1;
      break;
    case PIECE_L:
      pc->shape[0] =  3;
      pc->shape[1] =  3;
      pc->shape[2] =  3;
      pc->shape[3] =  3;
      pc->shape[4] = -1;
      pc->shape[5] = -1;
      break;
    case PIECE_J:
      pc->shape[0] =  4;
      pc->shape[1] =  4;
      pc->shape[2] =  4;
      pc->shape[3] = -1;
      pc->shape[4] = -1;
      pc->shape[5] =  4;
      break;
    case PIECE_Z:
      pc->shape[0] =  5;
      pc->shape[1] =  5;
      pc->shape[2] = -1;
      pc->shape[3] = -1;
      pc->shape[4] =  5;
      pc->shape[5] =  5;
      break;
    case PIECE_S:
      pc->shape[0] = -1;
      pc->shape[1] =  6;
      pc->shape[2] =  6;
      pc->shape[3] =  6;
      pc->shape[4] =  6;
      pc->shape[5] = -1;
      break;
    default: break;
  }

  return pc;
}

void piece_free(struct piece *pc) {
  assert(pc != NULL);

  free(pc);
}

void piece_rotate(struct piece *pc, int rotation) {

}

void piece_move(struct piece *pc, int dx, int dy) {
  assert(pc != NULL);
  pc->x += dx;
  pc->y += dy;
}