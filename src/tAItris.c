/**
 * @file    tAItris.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   Main file
 */

#include "tAItris.h"

int main() {
  random_init();

  gui_init();

  int running = 1;
  SDL_Event event;

  while (running) {

  }

  gui_free();

  return 0;
}