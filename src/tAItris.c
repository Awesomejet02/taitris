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

  PieceQueue *q = piece_queue_create();

  State *state = state_create();
  state_init(state, q);

  //while (state_step(state));

  debug_state_print(state);

  size_t s = 5;
  Input inputs[s];

  for (int i = 0; i < s; i++)
    inputs[i] = (Input) random_int(0, 6);

  state_apply_inputs(state, inputs, s);

  debug_state_print(state);

  state_free(state);
  piece_queue_free(q);

  return 0;
}