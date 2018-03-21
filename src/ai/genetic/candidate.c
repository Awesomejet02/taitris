/**
 * @file    candidate.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   No description
 */
#include "candidate.h"
#include "math.h"
#include "engine.h"

Candidate *genetic_candidate_create_random()
{
  Candidate *cdt = malloc(sizeof (Candidate));

  if (cdt == NULL)
    errx(EXIT_FAILURE, "Can't initialize Candidate object");

  cdt->coefs = genetic_aicoefs_random();
  cdt->fitness = 0;

  genetic_candidate_normalize(cdt);

  return cdt;
}

Candidate *genetic_candidate_create()
{
  Candidate *cdt = malloc(sizeof (Candidate));

  if (cdt == NULL)
    errx(EXIT_FAILURE, "Can't initialize Candidate object");

  cdt->coefs = calloc(1, sizeof(AiCoefs));

  if (cdt->coefs == NULL)
    errx(EXIT_FAILURE, "Can't initialize AiCoefs object");

  memset(cdt->coefs, 0, sizeof(AiCoefs));

  cdt->fitness = 0;

  return cdt;
}

void genetic_candidate_free(Candidate *candidate)
{
  assert(candidate != NULL);
  assert(candidate->coefs != NULL);

  genetic_aicoefs_free(candidate->coefs);
  free(candidate);
}

void genetic_candidate_normalize(Candidate *candidate)
{
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

Candidate *genetic_candidate_crossover(Candidate *cdt1, Candidate *cdt2)
{
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

void genetic_candidate_mutate(Candidate *cdt)
{
  assert(cdt != NULL);
  ((float*)cdt->coefs)[random_int(0, 4)] += random_double(-0.2, 0.2);
}