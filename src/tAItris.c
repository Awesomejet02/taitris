/**
 * @file    tAItris.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   Main file
 */

#include "tAItris.h"

int main() {
  random_init();

  SDL_Surface *win = gui_init();

  struct game_state *gs = gs_create();
  gs_init(gs);

  double last_time = time_get_current();

  struct input in;
  memset(&in, 0, sizeof(struct input));

  while(gs->state != GS_STATE_QUIT) {
    double new_time = time_get_current();
    double delta = new_time - last_time;
    last_time = new_time;

    event_handle(gs, &in);

    game_tick(delta, gs, &in);

    render_handle(win, gs);
  }

  gs_free(gs);
  gui_free(win);

  return 0;
}