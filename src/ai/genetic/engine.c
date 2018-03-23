/**
 * @file    engine.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Engine for the genetic algorithm
 */

#include "engine.h"
#include "../../utils/random.h"
#include "../../engine/state.h"
#include "../../engine/piece/piece.h"

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

AiBest *genetic_aibest_create(Piece *p, double s)
{
  AiBest *ab = malloc(sizeof(AiBest));

  if(ab == NULL)
  {
    errx(EXIT_FAILURE, "Can't initialize AiBest.");
  }

  ab->piece = p;
  ab->score = s;

  return ab;
}

void genetic_aibest_free(AiBest *ab)
{
  assert(ab != NULL);

  piece_free(ab->piece);
  free(ab);
}

AiBest *_genetic_best(State *state, int workingPieceIdx)
{//FIXME
  assert(state != NULL);
  assert(workingPieceIdx >= 0);
  assert(workingPieceIdx < 3);


  Piece *bestPiece = NULL;
  double bestScore = 0;
  //FIXME change this next line to put the working piece as the current_piece in state
  Piece *workingPiece = (workingPieceIdx) ? state->next_piece : state->current_piece;
  AiBest *aiBest = genetic_aibest_create(NULL, 0);

  for(int rotation = 0; rotation < 4; ++rotation){
    //FIXME SAVE PIECE ?
    for(int i = 0; i < rotation; ++i){
      state_apply_input(state, INPUT_ROTATE_LEFT);
    }

    while (state_apply_input(state, INPUT_MOVE_LEFT));

    do{
      //FIXME SAVE PIECE ?
      double score = 0;
      state_apply_input(state, INPUT_HARD_DROP);
      //FIXME STATE SAVE ?

      if (workingPieceIdx == 1)
      {
        score = genetic_get_rank(state);
      }
      else
      {
        AiBest *aiBest_rec = _genetic_best(state, workingPieceIdx + 1);
        score = aiBest_rec->score;
        genetic_aibest_free(aiBest_rec);
      }

      if (score > bestScore)
      {
        bestScore = score;
        bestPiece = workingPiece;
      }

    } while(state_apply_input(state, INPUT_MOVE_RIGHT));

  }

  aiBest->score = bestScore;
  aiBest->piece = bestPiece;

  return aiBest; //FIXME not shure if we do not create an other one
}

Piece *genetic_best(State *state)
{
  assert(state != NULL);

  State *state_cpy = state_copy(state);
  AiBest *aiBest = _genetic_best(state_cpy, 0);
  Piece *piece = aiBest->piece;
  genetic_aibest_free(aiBest);
  return piece;
}
