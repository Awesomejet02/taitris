/**
 * @file    motion.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Motion
 */
#ifndef TAITRIS_MOTION_H
#define TAITRIS_MOTION_H

#include "piece/piece.h"
#include "board.h"
#include "angle.h"

int motion_is_valid(const Piece *pc, const Board *brd);

int motion_try_move(Piece *pc, const Board *brd, int dx, int dy);

int motion_try_rotate(Piece *pc, const Board *brd, Rotation r);

int motion_try_down(Piece *pc, const Board *brd);

int motion_can_move(const Piece *pc, const Board *brd, int dx, int dy);

int motion_can_rotate(const Piece *pc, const Board *brd, Rotation r);

#endif //TAITRIS_MOTION_H
