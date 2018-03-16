/**
 * @file    input.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Input
 */
#ifndef TAITRIS_INPUT_H
#define TAITRIS_INPUT_H

#define INPUT_ESIZE 6
typedef enum {
  INPUT_MOVE_LEFT,
  INPUT_MOVE_RIGHT,
  INPUT_ROTATE_RIGHT,
  INPUT_ROTATE_LEFT,
  INPUT_SOFT_DROP,
  INPUT_HARD_DROP
} Input;

#endif //TAITRIS_INPUT_H
