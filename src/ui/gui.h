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

#define GUI_TITLE "tAItris"
#define GUI_WIDTH 200
#define GUI_HEIGHT 800

extern
SDL_Surface *gui_get_window(SDL_Surface *window);

extern inline
void gui_init();

extern inline
void gui_free();

extern inline
SDL_Surface* gui_load_image(char *path);

#endif //TAITRIS_GUI_H
