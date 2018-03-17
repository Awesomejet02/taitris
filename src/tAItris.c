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

  int loop = 1;
  int t = 0;

  while (loop) {
    t++;
    PieceQueue *q = piece_queue_create();

    State *state = state_create();
    state_init(state, q);

    State *prec = state_copy(state);

    while (state_step(state)) {
      if (prec->broken_lines != state->broken_lines && state->broken_lines == 3) {
        loop = 0;
        printf("Prec state %u\n", prec->broken_lines);
        debug_state_print(prec);
        printf("State %u\n", state->broken_lines);
        debug_state_print(state);
      }

      state_free(prec);
      prec = state_copy(state);
    }

    // debug_state_print(state);

    state_free(state);
    piece_queue_free(q);
  }

  printf("%d\n", t);

  return 0;
}