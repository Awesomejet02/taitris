/**
 * @file    event.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#ifndef TAITRIS_EVENT_H
#define TAITRIS_EVENT_H

#include <SDL.h>

#include "game_state.h"
#include "input.h"
#include "piece.h"

void event_handle(struct game_state *gs, struct input *in);

#endif //TAITRIS_EVENT_H
