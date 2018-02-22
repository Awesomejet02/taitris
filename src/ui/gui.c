/**
 * @file    gui.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "gui.h"

SDL_Surface* gui_init() {
  if(SDL_Init(SDL_INIT_VIDEO) == -1)
    errx(EXIT_FAILURE,"Could not initialize SDL: %s", SDL_GetError());

  if(TTF_Init() == -1)
    errx(EXIT_FAILURE, "Could not initialize TTF_Init: %s",
         TTF_GetError());

  SDL_Surface *win = NULL;

  SDL_putenv("SDL_VIDEO_WINDOW_POS=center");
  win = SDL_SetVideoMode(GUI_WIDTH, GUI_HEIGHT, 0,
                         SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF);
  SDL_WM_SetCaption(GUI_TITLE, NULL);
  SDL_FillRect(win, NULL, SDL_MapRGB(win->format, 0, 0, 0));
  SDL_Flip(win);

  return win;
}

void gui_free(SDL_Surface *win) {
  SDL_FreeSurface(win);
  SDL_Quit();
}

SDL_Surface* gui_load_image(char *path) {
  SDL_Surface *img;
  img = IMG_Load(path);

  if (!img) errx(EXIT_FAILURE, "Can't load %s: %s", path, IMG_GetError());

  return img;
}