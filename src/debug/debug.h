/**
 * @file    debug.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   No description
 */
#ifndef TAITRIS_DEBUG_H
#define TAITRIS_DEBUG_H

#include "../utils/ansi_code.h"

#define DEBUG_TAG(_name_, _color_) \
    ANSI_RESET \
  "[" ANSI_FG_CYAN "Debug" ANSI_RESET "]" \
  "(" _color_ _name_ ANSI_RESET ") "

#endif //TAITRIS_DEBUG_H
