/**
 * @file    candidate.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   No description
 */
#ifndef TAITRIS_CANDIDATE_H
#define TAITRIS_CANDIDATE_H

#include "engine.h"

typedef struct {
    AiCoefs *coefs;
    double fitness;
} Candidate;

Candidate *genetic_candidate_create();

void genetic_candidate_free(Candidate *candidate);

void genetic_candidate_normalize(Candidate *candidate);

Candidate *genetic_candidate_crossover(Candidate *cdt1, Candidate *cdt2);

void genetic_candidate_mutate(Candidate *cdt);

#endif //TAITRIS_CANDIDATE_H
