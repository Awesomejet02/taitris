/**
 * @file    tAItris.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   Main file
 */

#include "tAItris.h"

int main() {
  random_init();

  struct game_state *gs = gs_create(10, 22);
  gs_init(gs);

  board_merge_piece(gs->board, gs->piece_current);


  board_print(gs->board);


  gs_free(gs);

  return 0;
}