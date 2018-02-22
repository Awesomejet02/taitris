/**
 * @file    game.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "game.h"

void game_tick(double dt, struct game_state *gs, struct input *in) {
  static double tickDown = 0;
  static double tickMove = 0;
  tickDown += dt;
  tickMove += dt;

  int spawn = 0;

  if (tickMove > 0.1) {
    tickMove = 0;

    motion_try_move(&gs->piece_current, gs->board, in->moveX, 0);
    motion_try_rotate(&gs->piece_current, gs->board, in->rotate);

    if(!motion_try_move(&gs->piece_current, gs->board, 0, in->moveY))
      spawn = 1;

    if (in->moveX != 0) in->moveX = 0;
    if (in->moveY != 0) in->moveY = 0;
    if (in->rotate != 0) in->rotate = 0;

    if (in->down) {
      motion_try_move_down(&gs->piece_current, gs->board);
      in->down = 0;
    }
  }

  if (tickDown > 0.5) {
    tickDown = 0;

    if(!motion_try_move(&gs->piece_current, gs->board, 0, 1))
      spawn = 1;
  }

  size_t *lines;
  size_t count = board_get_completed_lines(gs->board, &lines);
  if (count) {
    board_break_lines(gs->board, lines);
    gs->score += count * 100;
  }

  if (spawn) {
    board_merge_piece(gs->board, gs->piece_current);
    gs_next_piece(gs);

    if (board_check_position(gs->board, gs->piece_current) == 0)
      gs->state = GS_STATE_QUIT;
  }
}