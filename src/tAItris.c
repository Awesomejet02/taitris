/**
 * @file    tAItris.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   Main file
 */

#include "tAItris.h"

#include <stdio.h>

int main() {
  random_init();

  struct game_state *gs = gs_create();
  gs_init(gs);

  motion_try_move_down(&gs->piece_current, gs->board);
  board_merge_piece(gs->board, gs->piece_current);

  gs_next_piece(gs);
  motion_try_move_down(&gs->piece_current, gs->board);
  board_merge_piece(gs->board, gs->piece_current);

  gs_next_piece(gs);
  motion_try_move_down(&gs->piece_current, gs->board);
  board_merge_piece(gs->board, gs->piece_current);
  
  gs_next_piece(gs);
  motion_try_move_down(&gs->piece_current, gs->board);
  board_merge_piece(gs->board, gs->piece_current);

  board_print(gs->board);

  gs_free(gs);

  return 0;
}