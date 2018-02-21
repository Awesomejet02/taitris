/**
 * @file    game.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#ifndef TAITRIS_GAME_H
#define TAITRIS_GAME_H

#include "game_state.h"

struct game_state *get_game_state();

void game_init();

int game_tick();

void game_quit();

#endif //TAITRIS_GAME_H
