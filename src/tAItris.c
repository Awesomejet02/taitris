/**
 * @file    tAItris.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   Main file
 */

#include "tAItris.h"

int main() {
  SDL_Surface *screen = NULL;
  screen = createMenu();
  eventManager(screen);

  return 0;
}