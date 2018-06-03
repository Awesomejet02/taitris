/**
 * @file    engine.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Engine for the genetic algorithm
 */

#include "engine.h"

AiCoefs *genetic_aicoefs_get() {
    static AiCoefs *coefs = NULL;

    if (!coefs) {
        coefs = malloc(sizeof(AiCoefs));

        if (coefs == NULL)
            errx(EXIT_FAILURE, "Can't initialize AiCoefs object");

        //precalculated coefs
        coefs->agg_height = -0.510066;
        coefs->clears = 0.760666;
        coefs->holes = -0.35663;
        coefs->bumpiness = -0.184483;
    }
    return coefs;
}

AiCoefs *genetic_aicoefs_random() {
    AiCoefs *coefs = malloc(sizeof(AiCoefs));

    if (coefs == NULL)
        errx(EXIT_FAILURE, "Can't initialize AiCoefs object");

    coefs->holes = random_double(-0.5, 0.5);
    coefs->agg_height = random_double(-0.5, 0.5);
    coefs->bumpiness = random_double(-0.5, 0.5);
    coefs->clears = random_double(-0.5, 0.5);

    return coefs;
}

void genetic_aicoefs_free(AiCoefs *coefs) {
    assert(coefs != NULL);

    free(coefs);
}

AiBest *genetic_aibest_create(Piece *p, double s) {
    AiBest *ab = malloc(sizeof(AiBest));

    if (ab == NULL)
        errx(EXIT_FAILURE, "Can't initialize AiBest.");

    ab->piece = p;
    ab->score = s;

    return ab;
}

void genetic_aibest_free(AiBest *ab) {
    assert(ab != NULL);

    piece_free(ab->piece);
    free(ab);
}

double genetic_get_rank(const State *state, AiCoefs *coefs) {

    double rank = coefs->bumpiness * genetic_tools_bumpiness(state);
    rank += coefs->clears * genetic_tools_clears(state);
    rank += coefs->agg_height * genetic_tools_aggregate_height(state);
    rank += coefs->holes * genetic_tools_holes(state);

    return rank;
}

AiBest *_genetic_best(const State *state, AiCoefs *coefs, int current, int max) {
    assert(coefs != NULL);
    assert(state != NULL);
    assert(current >= 0);
    assert(max >= current);

    AiBest *aiBest = genetic_aibest_create(
            piece_copy(state->current_piece),
            LONG_MIN
    );

    State *state_current = state_copy(state);
    State *state_next = NULL;
    double score = 0;

    for (int rotation = 0; rotation < ANGLE_ESIZE; ++rotation) {
        piece_set(state_current->current_piece, state->current_piece);

        for (int i = 0; i < rotation; ++i)
            state_apply_input(state_current, INPUT_ROTATE_LEFT);

        while (state_apply_input(state_current, INPUT_MOVE_LEFT));

        do {
            state_next = state_copy(state_current);

            state_apply_input(state_next, INPUT_HARD_DROP);

            if (current == max) {
                score = genetic_get_rank(state_next, coefs);
            } else {
                state_step(state_next);

                AiBest *aiBest_rec = _genetic_best(state_next, coefs, current + 1, max);
                score = aiBest_rec->score;
                genetic_aibest_free(aiBest_rec);
            }

            state_free(state_next);

            if (score > aiBest->score) {
                aiBest->score = score;
                piece_set(aiBest->piece, state_current->current_piece);
            }

        } while (state_apply_input(state_current, INPUT_MOVE_RIGHT));

    }

    state_free(state_current);

    return aiBest;
}

Piece *genetic_best(const State *state, AiCoefs *coefs) {
    assert(state != NULL);

    AiBest *aiBest = _genetic_best(state, coefs, 0, 1);

    Piece *piece = piece_copy(aiBest->piece);
    genetic_aibest_free(aiBest);

    return piece;
}
