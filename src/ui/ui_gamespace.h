/**
 * @file    ui_gamespace.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Gamespace
 */
#ifndef TAITRIS_UI_GAMESPACE_H
#define TAITRIS_UI_GAMESPACE_H

#include "ui.h"
#include "../engine/piece/piece_queue.h"
#include "../engine/state.h"
#include "../ai/genetic/engine.h"
#include "../debug/engine/debug_state.h"

#define UI_GAMESPACE_GLADE "./res/Gamespace.glade"
#define UNUSED(x) (void)(x)

void ui_gamespace_init();
void ui_gamespace_show(int mode);

#endif //TAITRIS_UI_GAMESPACE_H
