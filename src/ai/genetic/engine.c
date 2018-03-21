/**
 * @file    engine.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Engine for the genetic algorithm
 */

#include "engine.h"
#include "../../utils/random.h"
#include "../../engine/state.h"

double genetic_get_rank(State *state)
{
  Board *brd = state->board;
  AiCoefs *coefs = genetic_coefs_get();

  double rank = coefs->bumpiness * bumpiness(brd);
  rank += coefs->clears * clears(brd);
  rank += coefs->agg_height * aggregate_height(brd);
  rank += coefs->holes * holes(brd);

  return rank;
}

AiCoefs *genetic_coefs_get()
{
  static AiCoefs *coefs = NULL;

  if (!coefs)
  {
    coefs = malloc(sizeof(AiCoefs));
    //precalculated coefs
    coefs->agg_height = -0.510066;
    coefs->clears = 0.760666;
    coefs->holes = -0.35663;
    coefs->bumpiness = -0.184483;
  }
  return coefs;
}

AiCoefs *genetic_aicoefs_random()
{
  AiCoefs *coefs = malloc(sizeof(AiCoefs));

  if (coefs == NULL)
    errx(EXIT_FAILURE, "Can't initialize AiCoefs object");

  coefs->holes = random_double(-0.5, 0.5);
  coefs->agg_height = random_double(-0.5, 0.5);
  coefs->bumpiness = random_double(-0.5, 0.5);
  coefs->clears = random_double(-0.5, 0.5);

  return coefs;
}

void genetic_aicoefs_free(AiCoefs *coefs)
{
  assert(coefs != NULL);

  free(coefs);
}

