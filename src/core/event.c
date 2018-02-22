/**
 * @file    event.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "event.h"

void event_handle(struct game_state *gs, struct input *in) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        gs->state = GS_STATE_QUIT;
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_SPACE:
            in->rotate = PIECE_ROTATE_LEFT;
            break;
          case SDLK_UP:
            in->down = 1;
            break;
          case SDLK_DOWN:
            in->moveY = 1;
            break;
          case SDLK_RIGHT:
            in->moveX = 1;
            break;
          case SDLK_LEFT:
            in->moveX = -1;
            break;
          case SDLK_ESCAPE:
            in->quit = 1;
            break;
          default: break;
        }
        break;
      case SDL_KEYUP:
        switch (event.key.keysym.sym) {
          case SDLK_SPACE:
            in->rotate = 0;
            break;
          case SDLK_UP:
            in->down = 0;
            break;
          case SDLK_DOWN:
            in->moveY = 0;
            break;
          case SDLK_RIGHT:
            in->moveX = 0;
            break;
          case SDLK_LEFT:
            in->moveX = 0;
            break;
          case SDLK_ESCAPE:
            in->quit = 0;
            break;
          default: break;
        }
        break;
      default: break;
    }
  }
}