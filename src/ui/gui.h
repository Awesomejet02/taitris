/**
 * @file    gui.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#ifndef TAITRIS_GUI_H
#define TAITRIS_GUI_H

#include <stdlib.h>
#include <err.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../core/board.h"
#include "render.h"

#define GUI_TITLE "tAItris"
#define GUI_WIDTH (BOARD_WIDTH * RENDER_CELL_SIZE + 500)
#define GUI_HEIGHT (BOARD_HEIGHT * RENDER_CELL_SIZE)

extern inline
SDL_Surface* gui_init();

extern inline
void gui_free(SDL_Surface *win);

extern inline
SDL_Surface* gui_load_image(char *path);

#endif //TAITRIS_GUI_H
