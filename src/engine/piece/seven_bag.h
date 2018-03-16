/**
 * @file    seven_bag.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   7-Bag generator
 */
#ifndef TAITRIS_SEVEN_BAG_H
#define TAITRIS_SEVEN_BAG_H

#include "piece_type.h"
#include "../../utils/random.h"

void seven_bag_init(PieceType *bag);
void seven_bag_swap(PieceType *a, PieceType *b);
void seven_bag_shuffle(PieceType *bag);
PieceType seven_bag_draw();

#endif //TAITRIS_SEVEN_BAG_H
