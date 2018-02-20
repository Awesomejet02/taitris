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

int *generateRandom(int size, int cache);

void swap(int *tab, int a, int b);

void shuffle(int *tab);

int getRandom();

#endif //TAITRIS_RANDOM_H
