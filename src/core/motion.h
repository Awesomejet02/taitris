/**
 * @file    motion.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#ifndef TAITRIS_MOTION_H
#define TAITRIS_MOTION_H

#include "board.h"
#include "piece.h"

int motion_can_move(struct piece pc, const struct board *brd, int dx, int dy);
int motion_can_rotate(struct piece pc, const struct board *brd, int rotation);

int motion_try_move(struct piece *pc, const struct board *brd, int dx, int dy);
int motion_try_rotate(struct piece *pc, const struct board *brd, int rotation);

int motion_try_move_down(struct piece *pc, const struct board *brd);

#endif //TAITRIS_MOTION_H
