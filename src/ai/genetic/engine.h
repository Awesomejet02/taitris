/**
 * @file    engine.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Engine for the genetic algorithm
 */

#ifndef TAITRIS_ENGINE_H
#define TAITRIS_ENGINE_H

#include "tools.h"

typedef struct
{
    Piece *piece;
    double score;
} AiBest;

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

AiBest *genetic_aibest_create(Piece *p, double s);

void genetic_aibest_free(AiBest *ab);


#endif //TAITRIS_ENGINE_H
