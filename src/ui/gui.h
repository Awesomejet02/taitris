/**
 * @file    gui.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#ifndef TAITRIS_GUI_H
#define TAITRIS_GUI_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <err.h>

void init_SDL();

void init_TTF();

void wait_for_keypressed(void);

SDL_Surface *load_image(char *path);

SDL_Surface *initWindow(size_t x, size_t y);

#endif //TAITRIS_GUI_H
