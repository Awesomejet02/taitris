/**
 * @file    game.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#ifndef TAITRIS_GAME_H
#define TAITRIS_GAME_H

#include "game_state.h"
#include "motion.h"
#include "input.h"

void game_tick(double dt, struct game_state *gs, struct input *in);

#endif //TAITRIS_GAME_H
