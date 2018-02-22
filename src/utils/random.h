/**
 * @file    random.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#ifndef TAITRIS_RANDOM_H
#define TAITRIS_RANDOM_H

#include <stdlib.h>
#include <time.h>

extern inline
void random_init();

extern inline
size_t random_size_t(size_t min, size_t max);

extern inline
int random_int(int min, int max);

#endif //TAITRIS_RANDOM_H
