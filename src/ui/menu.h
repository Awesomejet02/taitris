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

TTF_Font *load_font(char *path, size_t size); //"../bin/font/font.ttf"

SDL_Surface *createMenu();

void eventManager();

#endif //TAITRIS_MENU_H
