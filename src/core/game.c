/**
 * @file    game.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "game.h"

struct game_state *get_game_state() {
  static struct game_state *gs = NULL;

  if (gs == NULL) gs = gs_create();

  return gs;
}

void game_init() {
  struct game_state *gs = get_game_state();
  gs_init(gs);

  while (game_tick()) {}

  game_quit();
}

int game_tick() {
  return 0;
}

void game_quit() {
  struct game_state *gs = get_game_state();
  gs_free(gs);
}