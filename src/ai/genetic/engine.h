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
    //double tetris;
    //double blockades;
} AiCoefs;

AiCoefs *get_coefs();

double get_rank(State *state);
#endif //TAITRIS_ENGINE_H
