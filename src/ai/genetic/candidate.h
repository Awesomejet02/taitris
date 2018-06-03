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

typedef struct {
    AiCoefs *coefs;
    double fitness;
} Candidate;

Candidate *genetic_candidate_create();

Candidate *genetic_candidate_create_random();

void genetic_candidate_free(Candidate *candidate);

void genetic_candidate_normalize(Candidate *candidate);

Candidate *genetic_candidate_crossover(Candidate *cdt1, Candidate *cdt2);

void genetic_candidate_mutate(Candidate *cdt);

int genetic_candidate_compare(const void *a ,const void *b);

void genetic_compute_fitness(Candidate **candidates, int population_len, State *state, PieceQueue *q);

void genetic_candidates_sort(Candidate **candidates, int population_len) ;

Candidate *learn();

#endif //TAITRIS_CANDIDATE_H
