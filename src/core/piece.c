/**
 * @file    piece.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "piece.h"

const int PIECE_SHAPES[7][4][4][4] = {
    // # PIECE_I
    // PIECE_ANGLE_UP
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_RIGHT
    0, 0, 1, 0,
    0, 0, 1, 0,
    0, 0, 1, 0,
    0, 0, 1, 0,

    // PIECE_ANGLE_DOWN
    0, 0, 0, 0,
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,

    // PIECE_ANGLE_LEFT
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,

    // # PIECE_O
    // PIECE_ANGLE_UP
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_RIGHT
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_DOWN
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_LEFT
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    // # PIECE_T
    // PIECE_ANGLE_UP
    0, 1, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_RIGHT
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_DOWN
    0, 0, 0, 0,
    1, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_LEFT
    0, 1, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

    // # PIECE_L
    // PIECE_ANGLE_UP
    0, 0, 1, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_RIGHT
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_DOWN
    0, 0, 0, 0,
    1, 1, 1, 0,
    1, 0, 0, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_LEFT
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

    // # PIECE_J
    // PIECE_ANGLE_UP
    1, 0, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_RIGHT
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_DOWN
    0, 0, 0, 0,
    1, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_LEFT
    0, 1, 0, 0,
    0, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,

    // # PIECE_Z
    // PIECE_ANGLE_UP
    1, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_RIGHT
    0, 0, 1, 0,
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_DOWN
    0, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_LEFT
    0, 1, 0, 0,
    1, 1, 0, 0,
    1, 0, 0, 0,
    0, 0, 0, 0,

    // # PIECE_S
    // PIECE_ANGLE_UP
    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_RIGHT
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_DOWN
    0, 0, 0, 0,
    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,

    // PIECE_ANGLE_LEFT
    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

};

void piece_random(struct piece *pc, size_t x, size_t y, int first) {
  assert(pc != NULL);

  pc->id = random_size_t(0, PIECE_COUNT);
  pc->x = x;
  pc->y = y;
  pc->angle = PIECE_ANGLE_UP;
  memcpy(pc->shapes, PIECE_SHAPES[pc->id], sizeof(int[4][4][4]));
}

void piece_move(struct piece *pc, int dx, int dy) {
  assert(pc != NULL);

  pc->x += dx;
  pc->y += dy;
}

int piece_can_move(struct piece pc, const struct board *brd, int dx, int dy) {
  assert(brd != NULL);

  struct piece npc;
  memcpy(&npc, &pc, sizeof(struct piece));
  piece_move(&npc, dx, dy);

  return board_check_position(brd, npc);
}


int piece_try_move(struct piece *pc, const struct board *brd, int dx, int dy) {
  assert(pc != NULL);
  assert(brd != NULL);

  if (piece_can_move(*pc, brd, dx, dy)) {
    piece_move(pc, dx, dy);
    return 1;
  }

  return 0;
}

void piece_rotate(struct piece *pc, int rotation) {
  assert(pc != NULL);

  pc->angle += rotation;
  pc->angle = pc->angle > 3 ? 0 : pc->angle;
  pc->angle = pc->angle < 0 ? 3 : pc->angle;
}

int piece_can_rotate(struct piece pc, const struct board *brd, int rotation) {
  assert(brd != NULL);

  struct piece npc;
  memcpy(&npc, &pc, sizeof(struct piece));
  piece_rotate(&npc, rotation);

  return board_check_position(brd, npc);
}

int piece_try_rotate(struct piece *pc, const struct board *brd, int rotation) {
  assert(pc != NULL);
  assert(brd != NULL);

  if (piece_can_rotate(*pc, brd, rotation)) {
    piece_rotate(pc, rotation);
    return 1;
  }

  return 0;
}