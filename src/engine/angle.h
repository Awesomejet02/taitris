/**
 * @file    angle.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Angle
 */
#ifndef TAITRIS_ANGLE_H
#define TAITRIS_ANGLE_H

#define ANGLE_ESIZE 4
typedef enum {
  ANGLE_UP,
  ANGLE_RIGHT,
  ANGLE_DOWN,
  ANGLE_LEFT,
} Angle;

typedef enum {
  ROTATE_LEFT = -1,
  ROTATE_RIGHT = 1
} Rotation;

static inline
Angle angle_rotate(Angle angle, Rotation rotation) {
  if (angle == ANGLE_UP && rotation == ROTATE_LEFT) angle = ANGLE_LEFT;
  else if (angle == ANGLE_LEFT && rotation == ROTATE_RIGHT) angle = ANGLE_UP;
  else angle += rotation;

  return angle;
}

#endif //TAITRIS_ANGLE_H
