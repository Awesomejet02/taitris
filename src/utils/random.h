/**
 * @file    random.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Random number generation
 */
#ifndef TAITRIS_RANDOM_H
#define TAITRIS_RANDOM_H

#include <stdlib.h>
#include <time.h>

static inline
void random_init() {
  srandom((unsigned int) time(NULL));
}

static inline
void random_init_seed(unsigned int seed) {
  srandom(seed);
}

static inline
int random_int(int min, int max) {
  return (int) (random() % (max - min) + min);
}

static inline
double random_double(double min, double max) {
  return ((double) random() / RAND_MAX) * (max - min) + min;
}

#endif //TAITRIS_RANDOM_H
