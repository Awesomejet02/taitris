/**
 * @file    menu.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#ifndef TAITRIS_MENU_H
#define TAITRIS_MENU_H

#include "gui.h"
#include "gameUI.h"
#include "../core/gameplay.h"

TTF_Font *load_font(char *path, int size);

SDL_Surface *createMenu();

void eventManager(SDL_Surface *screen);

#endif //TAITRIS_MENU_H
