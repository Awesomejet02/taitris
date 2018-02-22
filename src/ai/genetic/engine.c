//
// Created by dotty on 2/22/18.
//

#include "engine.h"
#include "../../core/board.h"

//TODO yolo
//TODO use copy board
//TODO use your brain
//TODO try movedown

struct ai_coefs *get_coefs()
{
  static struct ai_coefs *coefs = NULL;

  if (!coefs)
  {
    coefs = malloc(sizeof(struct ai_coefs));
    coefs->agg_height = -0.510066;
    coefs->clears = 0.760666;
    coefs->holes = -0.35663;
    coefs->bumpiness = -0.184483;
  }
  return coefs;
}

double get_rank(struct board *brd)
{
  struct ai_coefs *coefs = get_coefs();
  double rank = coefs->bumpiness * bumpiness(brd);
  rank += coefs->clears * clears(brd);
  rank += coefs->agg_height * aggregate_height(brd);
  rank += coefs->holes * holes(brd);
  return rank;
}