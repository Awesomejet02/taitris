/**
 * @file    engine.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Engine for the genetic algorithm
 */

#ifndef TAITRIS_ENGINE_H
#define TAITRIS_ENGINE_H

#include "tools.h"

typedef struct {
    double agg_height;
    double holes;
    double clears;
    double bumpiness;
} AiCoefs;

double genetic_get_rank(State *state);

AiCoefs *genetic_coefs_get();

AiCoefs *genetic_aicoefs_random();

void genetic_aicoefs_free(AiCoefs *coefs);

#endif //TAITRIS_ENGINE_H
