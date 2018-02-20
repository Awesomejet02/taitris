/**
 * @file    menu.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "menu.h"

TTF_Font *load_font(char *path, size_t size) //"../bin/font/font.ttf"
{
  TTF_Font *font = NULL;
  font = TTF_OpenFont(path, size);
  if (!font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }
  return font;
}

SDL_Surface *createMenu() {
  SDL_Surface *screen, *toBlit, *logo, *background = NULL;
  SDL_Rect _play = {430, 270, 0, 0}, _quit = {430, 330, 0, 0};
  SDL_Rect _logo = {257, 50, 0, 0}, _background = {0, 0, 0, 0};
  TTF_Font *font = NULL;
  SDL_Color white_color = {255, 255, 255, 0};
  screen = initWindow(960, 540);
  background = load_image("res/sprites/background.bmp");
  SDL_BlitSurface(background, NULL, screen, &_background);
  logo = load_image("res/sprites/logo.bmp");
  SDL_BlitSurface(logo, NULL, screen, &_logo);
  init_TTF();
  font = load_font("res/font/font.ttf", 50);
  toBlit = TTF_RenderText_Blended(font, "PLAY", white_color);
  SDL_BlitSurface(toBlit, NULL, screen, &_play);
  toBlit = TTF_RenderText_Blended(font, "QUIT", white_color);
  SDL_BlitSurface(toBlit, NULL, screen, &_quit);
  SDL_Flip(screen);
  SDL_FreeSurface(toBlit);
  SDL_FreeSurface(logo);
  SDL_FreeSurface(background);
  return screen;
}

void eventManager(SDL_Surface *screen) {
  int proceed = 1;
  SDL_Event event;
  while (proceed) {
    // Take an event
    SDL_WaitEvent(&event);
    // Switch on event type
    switch (event.type) {
      // Someone pressed a key -> leave the function
      case SDL_QUIT: /* Quit */
        proceed = 0;
        break;
      case SDL_KEYDOWN: /* Si appui sur une touche */
        switch (event.key.keysym.sym) {
          case SDLK_RETURN: // key_return : launch the recognition
          case SDLK_SPACE: // key_space : launch the recognition
            proceed = 0;
            createWindow(screen);
            play(screen);
            wait_for_keypressed();
            break;
          case SDLK_q:proceed = 0;
            break;
          default: break;
        }
        break;
      default: break;
    }
  }
}
