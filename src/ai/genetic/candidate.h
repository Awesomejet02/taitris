/**
 * @file    candidate.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Candidate
 */
#ifndef TAITRIS_CANDIDATE_H
#define TAITRIS_CANDIDATE_H

#include <math.h>

#include "engine.h"
#include "../../engine/board.h" //Needed ?

typedef struct {
    AiCoefs *coefs;
    double fitness;
} Candidate;

void tune(size_t cdt_len, size_t nCdt_len, size_t epoch, char *path);

#endif //TAITRIS_CANDIDATE_H
