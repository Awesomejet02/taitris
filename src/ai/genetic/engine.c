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

double genetic_get_rank(State *state) {
  assert(state != NULL);

  AiCoefs *coefs = genetic_coefs_get();

  double rank = coefs->bumpiness * bumpiness(state);
  rank += coefs->clears * clears(state);
  rank += coefs->agg_height * aggregate_height(state);
  rank += coefs->holes * holes(state);

  return rank;
}

AiCoefs *genetic_coefs_get() {
  static AiCoefs *coefs = NULL;

  if (!coefs) {
    coefs = malloc(sizeof(AiCoefs));
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

  if (ab == NULL) {
    errx(EXIT_FAILURE, "Can't initialize AiBest.");
  }

  ab->piece = p;
  ab->score = s;

  return ab;
}

void genetic_aibest_free(AiBest *ab) {
  assert(ab != NULL);

  piece_free(ab->piece);
  free(ab);
}

AiBest *_genetic_best(State *state,
                      Piece *workingPieces[2],
                      int workingPieceIdx) {
  assert(state != NULL);
  assert(workingPieces != NULL);
  assert(workingPieceIdx >= 0);
  assert(workingPieceIdx < 2);

  Piece *bestPiece = NULL;
  double bestScore = 0;
  Piece *workingPiece = NULL;
  State *state_cpy = NULL;

  if (workingPieceIdx == 0) {
    workingPiece = piece_copy(workingPieces[0]); // FREE OK
  } else {
    workingPiece = piece_copy(workingPieces[1]); // FREE OK
  }

  for (int rotation = 0; rotation < 4; ++rotation) {
    piece_free(state->current_piece);
    state->current_piece = piece_copy(workingPiece); // FREE avec la state

    for (int i = 0; i < rotation; ++i) {
      state_apply_input(state, INPUT_ROTATE_LEFT);
    }

    while (state_apply_input(state, INPUT_MOVE_LEFT));

    do {
      state_cpy = state_copy(state); // FREE OK
      state_apply_input(state_cpy, INPUT_HARD_DROP);

      double score = 0;
      if (workingPieceIdx == 1) {
        score = genetic_get_rank(state_cpy);
      } else {
        state_step(state_cpy);
        
        AiBest *aiBest_rec = _genetic_best(state_cpy,
                                           workingPieces,
                                           workingPieceIdx + 1); // FREE OK
        score = aiBest_rec->score;
        genetic_aibest_free(aiBest_rec);
      }

      state_free(state_cpy);

      if (score > bestScore) {
        bestScore = score;
        bestPiece = state->current_piece;
      }

    } while (state_apply_input(state, INPUT_MOVE_RIGHT));

  }

  piece_free(workingPiece);

  return genetic_aibest_create(piece_copy(bestPiece), bestScore);
}

Piece *genetic_best(State *state) {
  assert(state != NULL);

  State *state_cpy = state_copy(state); // FREE OK
  Piece *workingPieces[2] = {
      piece_copy(state_cpy->current_piece), // FREE OK
      piece_copy(state_cpy->next_piece) // FREE OK
  };

  AiBest *aiBest = _genetic_best(state_cpy, workingPieces, 0); // FREE OK

  Piece *piece = piece_copy(aiBest->piece); // User need handle the free

  genetic_aibest_free(aiBest);
  piece_free(workingPieces[0]);
  piece_free(workingPieces[1]);
  state_free(state_cpy);

  return piece;
}
