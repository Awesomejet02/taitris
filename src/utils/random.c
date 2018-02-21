/**
 * @file    random.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "random.h"

void random_init() {
  struct timespec curr;
  clock_gettime(CLOCK_MONOTONIC, &curr);

  unsigned int seed = (unsigned int) curr.tv_sec * 1000000000 + ((unsigned int) curr.tv_nsec);

  srandom(seed);
}

size_t random_size_t(size_t min, size_t max) {
  return (size_t) random() % (max - min) + min;
}

int random_int(int min, int max) {
  return (int) random() % (max - min) + min;
}