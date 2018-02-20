/**
 * @file    gameplay.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#ifndef TAITRIS_GAMEPLAY_H
#define TAITRIS_GAMEPLAY_H

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL.h>
#include "game.h"
#include "../ui/gui.h"
#include "../ui/gameUI.h"
#include "../utils/random.h"
#include "score.h"

void play(SDL_Surface *screen);

#endif //TAITRIS_GAMEPLAY_H
