/**
 * @file    tAItris.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Main file
 */

#include "utils/random.h"

#include "engine/piece/piece_queue.h"
#include "engine/state.h"

#include "debug/engine/debug_state.h"

int main() {
  random_init();

  unsigned int seed = (unsigned int) time(NULL);
  PieceQueue *q = piece_queue_create(seed);

  PieceType t;

  t = piece_queue_get(q, 0);

  t = piece_queue_get(q, 1);

  t = piece_queue_get(q, 2);

  t = piece_queue_get(q, 3);

  t = piece_queue_get(q, 4);

  t = piece_queue_get(q, 9);

  t = piece_queue_get(q, 4552);

  piece_queue_free(q);

  return 0;
}