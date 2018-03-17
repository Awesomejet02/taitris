//
// Created by dotty on 2/22/18.
//

#include "engine.h"
#include "../../engine/state.h"

AiCoefs *get_coefs()
{
  static AiCoefs *coefs = NULL;

  if (!coefs)
  {
    coefs = malloc(sizeof(AiCoefs));
    coefs->agg_height = -0.510066;
    coefs->clears = 0.760666;
    coefs->holes = -0.35663;
    coefs->bumpiness = -0.184483;
  }
  return coefs;
}

double get_rank(State *state)
{
  Board *brd = state->board;
  AiCoefs *coefs = get_coefs();

  double rank = coefs->bumpiness * bumpiness(brd);
  rank += coefs->clears * clears(brd);
  rank += coefs->agg_height * aggregate_height(brd);
  rank += coefs->holes * holes(brd);

  return rank;
}