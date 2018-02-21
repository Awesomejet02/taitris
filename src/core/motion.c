/**
 * @file    motion.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "motion.h"

int motion_can_move(struct piece pc, const struct board *brd, int dx, int dy) {
  assert(brd != NULL);

  struct piece npc;
  memcpy(&npc, &pc, sizeof(struct piece));
  piece_move(&npc, dx, dy);

  return board_check_position(brd, npc);
}

int motion_can_rotate(struct piece pc, const struct board *brd, int rotation) {
  assert(brd != NULL);

  struct piece npc;
  memcpy(&npc, &pc, sizeof(struct piece));
  piece_rotate(&npc, rotation);

  return board_check_position(brd, npc);
}

int motion_try_move(struct piece *pc, const struct board *brd, int dx, int dy) {
  assert(pc != NULL);
  assert(brd != NULL);

  if (motion_can_move(*pc, brd, dx, dy)) {
    piece_move(pc, dx, dy);
    return 1;
  }

  return 0;
}

int motion_try_rotate(struct piece *pc, const struct board *brd, int rotation) {
  assert(pc != NULL);
  assert(brd != NULL);

  if (motion_can_rotate(*pc, brd, rotation)) {
    piece_rotate(pc, rotation);
    return 1;
  }

  return 0;
}

int motion_try_move_down(struct piece *pc, const struct board *brd) {
  assert(pc != NULL);
  assert(brd != NULL);

  int moved = 0;

  while (motion_try_move(pc, brd, 0, 1))
    moved = 1;

  return moved;
}