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
#include "ai/genetic/candidate.h"

int main() {
  random_init();

  tune(30, 10, 50, "/tmp/save.ai");

  genetic_aicoefs_free(genetic_aicoefs_get());
  return 0;
}