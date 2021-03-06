/**
 * @file    engine.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Engine for the genetic algorithm
 */

#ifndef TAITRIS_ENGINE_H
#define TAITRIS_ENGINE_H

#include <stdlib.h>
#include <assert.h>
#include <err.h>
#include <limits.h>

#include "tools.h"
#include "../../engine/state.h"
#include "../../engine/piece/piece.h"
#include "../../utils/random.h"

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

AiCoefs *genetic_aicoefs_get();

AiCoefs *genetic_aicoefs_random();

void genetic_aicoefs_free(AiCoefs *coefs);

AiBest *genetic_aibest_create(Piece *p, double s);

void genetic_aibest_free(AiBest *ab);

Piece *genetic_best(const State *state,  AiCoefs *coefs) ;

#endif //TAITRIS_ENGINE_H
