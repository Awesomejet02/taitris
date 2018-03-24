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


void array_shift_left(int *tab, size_t *len, size_t pos)
{
  assert(*len > pos);
  for(size_t i = pos; i < *len - 1; i++)
  {
    tab[i] = tab[i + 1];
  }
  tab[*len - 1] = -1;
  (*len)--;
}

int *array_remove_one(int* arr, size_t len, size_t pos)
{
  assert(arr != NULL);
  assert(len > 0);
  assert(pos > 0);
  assert(pos <= len);

  int *dst = malloc((len - 1) * sizeof(int));

  memcpy(dst, arr, pos * sizeof(int));
  memcpy(dst + pos, arr + pos + 1, (len - pos - 1) * sizeof(int));
  return dst;
}

Candidate **genetic_tournament_select_pair(Candidate **cdt, size_t ways)
{
  assert(cdt != NULL);

  size_t cdt_len = sizeof(cdt) / sizeof(cdt[0]); //FIXME does not work, use define to 100
  assert(cdt_len >= 2);
  Candidate **res = malloc(sizeof(Candidate) * 2);
  int *indices = malloc(cdt_len * sizeof(int)); //TO BE ASSIGNABLE HAVE TO DE MALLOCED
  for(size_t i = 0; i < cdt_len; i++)
  {
    indices[i] = i;
  }
  int fittestCandidateIndex1 = -1;
  int fittestCandidateIndex2 = -1;
  int selectedIndex = 0;
  int toDelete = 0;
  for(size_t i = 0; i < ways; i++)
  {
    toDelete = random_int(0, cdt_len);
    selectedIndex = indices[toDelete];
    //array_shift_left(indices, &cdt_len, toDelete);
    int *tmp = array_remove_one(indices, cdt_len--, toDelete);
    free(indices);
    indices = tmp;
    if(fittestCandidateIndex1 == -1 || selectedIndex < fittestCandidateIndex1)
    {
      fittestCandidateIndex2 = fittestCandidateIndex1;
      fittestCandidateIndex1 = selectedIndex;
    }
    else if(fittestCandidateIndex2 == -1 || selectedIndex < fittestCandidateIndex2)
    {
        fittestCandidateIndex2 = selectedIndex;
    }

    res[1] = cdt[fittestCandidateIndex1];
    res[2] = cdt[fittestCandidateIndex2];

  }
  free(indices);
  return res;
}
