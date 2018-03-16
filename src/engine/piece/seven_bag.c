/**
 * @file    seven_bag.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   7-Bag generator
 */
#include "seven_bag.h"

void seven_bag_init(PieceType *bag) {
  for (int i = 0; i < PIECE_TYPE_ESIZE; i++) {
    bag[i] = (PieceType) i;
  }
}

void seven_bag_swap(PieceType *a, PieceType *b) {
  PieceType tmp = *a;
  *a = *b;
  *b = tmp;
}

void seven_bag_shuffle(PieceType *bag) {
  for (int i = (PIECE_TYPE_ESIZE - 1); i > 0; i--) {
    int j = random_int(0, i + 1);
    seven_bag_swap(bag + i, bag + j);
  }
}

PieceType seven_bag_draw() {
  static PieceType bag[PIECE_TYPE_ESIZE];
  static int index = PIECE_TYPE_ESIZE;

  if (index == PIECE_TYPE_ESIZE) {
    seven_bag_init(bag);
    seven_bag_shuffle(bag);
    index = 0;
  }

  PieceType draw = bag[index];
  index++;
  return draw;
}