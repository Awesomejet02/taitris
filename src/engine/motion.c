/**
 * @file    motion.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Motion
 */
#include "motion.h"

int motion_is_valid(const Piece *pc, const Board *brd) {
  if (pc == NULL || brd == NULL) return 0;

  for (int i = 0; i < PIECE_SHAPE_HEIGHT; i++) {
    for (int j = 0; j < PIECE_SHAPE_WIDTH; j++) {
      if (pc->shape->shape[pc->angle][i][j]) {
        int x = pc->x + j;
        int y = pc->y - i;

        if (x < 0 || y < 0 ||
            x >= brd->width || y >= (brd->height + BOARD_HIDDEN) ||
            (y < brd->height && board_at(brd, x, y) != CELL_EMPTY))
          return 0;
      }
    }
  }

  return 1;
}

int motion_try_move(Piece *pc, const Board *brd, int dx, int dy) {
  if (pc == NULL || brd == NULL) return 0;

  piece_move(pc, dx, dy);

  if (!motion_is_valid(pc, brd)) {
    piece_move(pc, -dx, -dy);
    return 0;
  }

  return 1;
}

int motion_try_down(Piece *pc, const Board *brd) {
  if (pc == NULL || brd == NULL) return 0;

  int moved = 0;

  while (motion_try_move(pc, brd, 0, -1))
    moved++;

  return moved;
}

int motion_try_rotate(Piece *pc, const Board *brd, Rotation r) {
  if (pc == NULL || brd == NULL) return 0;

  piece_rotate(pc, r);

  if (!motion_is_valid(pc, brd)) {
    piece_rotate(pc, r == ROTATE_LEFT ? ROTATE_RIGHT : ROTATE_LEFT);
    return 0;
  }

  return 1;
}

int motion_can_move(const Piece *pc, const Board *brd, int dx, int dy) {
  if (pc == NULL || brd == NULL) return 0;

  Piece *try = piece_copy(pc);
  int is_valid = motion_try_move(try, brd, dx, dy);
  piece_free(try);
  return is_valid;
}

int motion_can_rotate(const Piece *pc, const Board *brd, Rotation r) {
  if (pc == NULL || brd == NULL) return 0;

  Piece *try = piece_copy(pc);
  int is_valid = motion_try_rotate(try, brd, r);
  piece_free(try);
  return is_valid;
}