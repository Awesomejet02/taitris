/**
 * @file    tAItris.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Main file
 */

#include "utils/random.h"

#include "engine/piece/piece_queue.h"
#include "engine/state.h"
#include "ai/genetic/engine.h"

#include "debug/engine/debug_state.h"

int main() {
  random_init();

  unsigned int seed = (unsigned int) time(NULL);
  PieceQueue *q = piece_queue_create(seed);

  State *state = state_create();
  state_init(state, q);

  do {
    //debug_state_print(state);
    //system("read p");

    Piece *pc = genetic_best(state);

    piece_free(state->current_piece);
    state->current_piece = pc;

    //debug_state_print(state);
    //system("read p");

    system("read p");

    state_apply_input(state, INPUT_HARD_DROP);
  } while (state_step(state));

  state_free(state);
  piece_queue_free(q);

  return 0;
}