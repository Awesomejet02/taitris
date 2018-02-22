/**
 * @file    timing.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "timing.h"

double time_get_current() {
  struct timespec curr;
  clock_gettime(CLOCK_MONOTONIC, &curr);

  return (double) curr.tv_sec + ((double) curr.tv_nsec / 1000000000);
}