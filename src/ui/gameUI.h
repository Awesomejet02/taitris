/**
 * @file    gameUI.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#ifndef TAITRIS_GAMEUI_H
#define TAITRIS_GAMEUI_H

#include "gui.h"
#include "../core/game.h"
#include "menu.h"

SDL_Surface **load_sprites();

SDL_Surface *createWindow(SDL_Surface *screen);

SDL_Surface *displayBoard(SDL_Surface *screen, board *board, SDL_Surface **sp);

#endif //TAITRIS_GAMEUI_H
