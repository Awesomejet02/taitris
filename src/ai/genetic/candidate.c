/**
 * @file    candidate.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Candidate
 */

#define EPOCH 2
#define POPULATION_SIZE 100
#define MAX_MOVES 800

#include <stdlib.h>

#include "candidate.h"
#include "engine.h"
#include "../../engine/state.h"

Candidate *genetic_candidate_create() {
    Candidate *cdt = malloc(sizeof(Candidate));

    if (cdt == NULL)
        errx(EXIT_FAILURE, "Can't initialize Candidate object");

    cdt->coefs = malloc(sizeof(AiCoefs));

    if (cdt->coefs == NULL)
        errx(EXIT_FAILURE, "Can't initialize AiCoefs object");

    memset(cdt->coefs, 0, sizeof(AiCoefs));

    cdt->fitness = 0;

    return cdt;
}

Candidate *genetic_candidate_create_random() {
    Candidate *cdt = malloc(sizeof (Candidate));

    if (cdt == NULL)
        errx(EXIT_FAILURE, "Can't initialize Candidate object");

    cdt->coefs = genetic_aicoefs_random();
    cdt->fitness = random_double(0, 10000);

    genetic_candidate_normalize(cdt);

    return cdt;
}

Candidate *genetic_candidate_copy(Candidate *cdt) {
    assert(cdt != NULL);

    Candidate *rt = genetic_candidate_create();

    rt->coefs->agg_height = cdt->coefs->agg_height;
    rt->coefs->bumpiness = cdt->coefs->bumpiness;
    rt->coefs->clears = cdt->coefs->clears;
    rt->coefs->holes = cdt->coefs->holes;
    rt->fitness = cdt->fitness;

    return rt;
}

void genetic_candidate_free(Candidate *candidate) {
    assert(candidate != NULL);
    assert(candidate->coefs != NULL);

    genetic_aicoefs_free(candidate->coefs);
    free(candidate);
}

void genetic_candidate_normalize(Candidate *candidate) {
    assert(candidate != NULL);
    assert(candidate->coefs != NULL);

    double norm = sqrt(
            pow(candidate->coefs->agg_height, 2) +
            pow(candidate->coefs->clears, 2) +
            pow(candidate->coefs->holes, 2) +
            pow(candidate->coefs->bumpiness, 2));

    candidate->coefs->clears /= norm;
    candidate->coefs->bumpiness /= norm;
    candidate->coefs->holes /= norm;
    candidate->coefs->agg_height /= norm;
}

Candidate *genetic_candidate_crossover(Candidate *cdt1, Candidate *cdt2) {
    assert(cdt1 != NULL);
    assert(cdt2 != NULL);
    assert(cdt1->coefs != NULL);
    assert(cdt2->coefs != NULL);

    double cdt1_f = cdt1->fitness;
    double cdt2_f = cdt2->fitness;

    Candidate *cdt = genetic_candidate_create();

    cdt->coefs->agg_height =
            cdt1_f * cdt1->coefs->agg_height +
            cdt2_f * cdt2->coefs->agg_height;
    cdt->coefs->holes =
            cdt1_f * cdt1->coefs->holes +
            cdt2_f * cdt2->coefs->holes;
    cdt->coefs->bumpiness =
            cdt1_f * cdt1->coefs->bumpiness +
            cdt2_f * cdt2->coefs->bumpiness;
    cdt->coefs->clears =
            cdt1_f * cdt1->coefs->bumpiness +
            cdt2_f * cdt2->coefs->bumpiness;
    genetic_candidate_normalize(cdt);

    return cdt;
}

void genetic_candidate_mutate(Candidate *cdt) {
    assert(cdt != NULL);

    ((float*)cdt->coefs)[random_int(0, 4)] += random_double(-0.2, 0.2);
}

void genetic_candidates_print(Candidate **candidates, int len){
    for (int i = 0; i < len; ++i){
        printf("| %d ", (int)candidates[i]->fitness);
    }
    printf("|\n");
}

void genetic_compute_fitness(Candidate **candidates, int population_len, State *state, PieceQueue *q){
    assert(candidates != NULL);
    assert(population_len > 0);
    assert(state != NULL);
    assert(q != NULL);

    for(int i = 0; i < population_len; ++i) {
        int numberOfMoves = 0;
        state_init(state, q); // restore the base state
        do {
            //state->current_piece = malloc(sizeof(Piece));
            Piece *f_piece = state->current_piece;
            state->current_piece = genetic_best(state, candidates[i]->coefs);
            piece_free(f_piece);
        } while (numberOfMoves++ < MAX_MOVES && state_step(state));
        candidates[i]->fitness = state->score + state->broken_lines + state->level;
    }
}

int genetic_candidate_compare(const void *a ,const void *b){ // put in decreasing order
    const Candidate *f = *(Candidate **)a;
    const Candidate *s = *(Candidate **)b;
    return s->fitness - f->fitness;
};

void genetic_candidates_sort(Candidate **candidates, int population_len) {
    assert(candidates != NULL);
    assert(population_len > 0);
    genetic_candidates_print(candidates, 10);
    qsort(candidates, population_len, sizeof(Candidate*), genetic_candidate_compare);
    genetic_candidates_print(candidates, 10);
}

Candidate *learn() {
    //create population of candidates
    Candidate **candidates = malloc(POPULATION_SIZE * sizeof(Candidate*));
    for (int i = 0; i < POPULATION_SIZE; ++i){
        candidates[i] = genetic_candidate_create_random();
    }

    //create game
    unsigned int seed = (unsigned int) time(NULL);
    PieceQueue *q = piece_queue_create(seed);
    State *state = state_create();

    genetic_compute_fitness(candidates, POPULATION_SIZE, state, q);
    genetic_candidates_sort(candidates, POPULATION_SIZE);

    printf("first fitest: %f\nholes: %f\nclears: %f\nbumpiness: %f\nagg_height: %f\n",
           candidates[0]->fitness,
           candidates[0]->coefs->holes,
           candidates[0]->coefs->clears,
           candidates[0]->coefs->bumpiness,
           candidates[0]->coefs->agg_height);


    int epoch = 0;

    while(epoch++ < EPOCH){
        int newLen = (POPULATION_SIZE/100)*30;

        for(int i = 0, j = 0; i < newLen; ++i, ++j){
            int idx = POPULATION_SIZE - 1 - i;

            genetic_candidate_free(candidates[idx]);
            candidates[idx] = genetic_candidate_crossover(candidates[0], candidates[i+1]);

            if ( random_int(0, 100) < 30){
                genetic_candidate_mutate(candidates[idx]);
            }

            genetic_candidate_normalize(candidates[idx]);
        }

        genetic_compute_fitness(candidates, POPULATION_SIZE, state, q);
        genetic_candidates_sort(candidates, POPULATION_SIZE);
        printf("new fitest: %f\nholes: %f\nclears: %f\nbumpiness: %f\nagg_height: %f\n",
               candidates[0]->fitness,
               candidates[0]->coefs->holes,
               candidates[0]->coefs->clears,
               candidates[0]->coefs->bumpiness,
               candidates[0]->coefs->agg_height);
    }

    Candidate *best = genetic_candidate_copy(candidates[0]);

    for(int i = 0; i < POPULATION_SIZE; ++i) {
        genetic_candidate_free(candidates[i]);
    }
    state_free(state);
    piece_queue_free(q);

    return best;
}

