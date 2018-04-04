/**
 * @file    candidate.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Candidate
 */

#include "candidate.h"

Candidate *genetic_candidate_create()
{
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

Candidate **genetic_tournament_select_pair(Candidate **cdt, size_t ways, size_t cdt_len)
{
  assert(cdt != NULL);

  //size_t cdt_len = sizeof(cdt) / sizeof(cdt[0]);
  assert(cdt_len >= 2);
  Candidate **res = malloc(sizeof(Candidate) * 2);
  int indices[cdt_len];
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
    array_shift_left(indices, &cdt_len, toDelete);
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
  return res;
}

int grid_is_exceeded(Board *board)
{
  return !board_is_line_empty(board, 0) || !board_is_line_empty(board, 1);
}

void computeFitness(Candidate **cdt, size_t cdt_len, size_t nbOfGames, size_t maxNbOfMoves)
{
  assert(cdt != NULL);

  //Testing
  size_t workingPieces_len = 2;
  Piece **workingPieces = malloc(sizeof(Piece) * workingPieces_len);// = genetic_best(state);

  //

  for(size_t i = 0; i < cdt_len; i++)
  {
    Candidate cur_cdt = *cdt[i];
    AiCoefs* ai = genetic_aicoefs_create(cur_cdt.coefs->holes, cur_cdt.coefs->agg_height, cur_cdt.coefs->bumpiness, cur_cdt.coefs->clears);
    double totalScore = 0;
    double score = 0;
    for(size_t j = 0; j < nbOfGames; j++)
    {
      State *state = state_create();

      //Working piece(s)
      /*size_t workingPieces_len = 2;
      Piece **workingPieces = malloc(sizeof(Piece) * workingPieces_len);// = genetic_best(state);*/
      workingPieces[0] = state_create_piece(state);
      workingPieces[1] = state_create_piece(state);
      Piece *workingPiece = workingPieces[0];
      size_t nbOfMoves = 1; //He starts his while with a "++" on nbOfMoves
      while(nbOfMoves < maxNbOfMoves && grid_is_exceeded(state->board))
      {
        workingPiece = genetic_best(state);
        //Faire descendre la piece
        //TODO
        ///
        score += 1; //A modifier en fonction du calcul de score
        for (size_t k = 0; k < workingPieces_len - 1; k++)
        {
          workingPieces[k] = workingPieces[k + 1];
        }
        workingPieces[workingPieces_len - 1] = state_create_piece(state);
        workingPiece = workingPieces[0];
        nbOfMoves++;
      }

      totalScore += score;
    }
    cur_cdt.fitness = totalScore;
  }
  //free
  free(workingPieces);
}

void deleteNLastReplacement(Candidate **cdt_tab, Candidate **new_cdt_tab, size_t cdt_len, size_t nCdt_len)
{
  assert(nCdt_len < cdt_len);
  for (size_t i = cdt_len - nCdt_len; i < cdt_len; i++)
  {
    cdt_tab[i] = new_cdt_tab[i - cdt_len - nCdt_len];
  }
}

//Need to be tested
void sort(Candidate cdt_tab[], int len)
{
   int i, j;
   double key;
   for (i = 1; i < len; i++)
   {
       key = cdt_tab[i].fitness;
       j = i-1;
       while (j >= 0 && cdt_tab[j].fitness > key)
       {
           cdt_tab[j + 1].fitness = cdt_tab[j].fitness;
           j = j-1;
       }
       cdt_tab[j + 1].fitness = key;
   }
}

void tune(size_t cdt_len, size_t nCdt_len)
{
  Candidate **cdt_tab = malloc(sizeof(Candidate) * cdt_len);
  for (size_t i = 0; i < cdt_len; i++)
  {
    cdt_tab[i] = genetic_candidate_create_random();
  }
  printf("Computing fitnesses of initial population...\n");
  computeFitness(cdt_tab, cdt_len, 5, 200);
  //need to sort cdt_tab

  int count = 0;
  Candidate **pair;
  Candidate* cdt;
  Candidate **new_cdt_tab = malloc(sizeof(Candidate) * nCdt_len);
  while(1)
  {
    //new_cdt_tab = malloc(sizeof(Candidate) * nCdt_len);
    for (size_t i = 0; i < nCdt_len; i++)
    {
      pair = genetic_tournament_select_pair(cdt_tab, 10, cdt_len);
      cdt = genetic_candidate_crossover(pair[0], pair[1]);
      if(random_double(0, 1) < 0.05)
      {
        genetic_candidate_mutate(cdt);
      }
      genetic_candidate_normalize(cdt);
      new_cdt_tab[i] = cdt;
    }
    printf("Computing fitnesses of new candidates. (%d)\n", count);
    computeFitness(new_cdt_tab, nCdt_len, 5, 200);
    deleteNLastReplacement(cdt_tab, new_cdt_tab, cdt_len, nCdt_len);
    int totalFitness = 0;
    for (size_t i = 0; i < cdt_len; i++)
    {
      totalFitness += cdt_tab[i]->fitness;
    }
    printf("Average fitness = %zu\n", totalFitness/cdt_len);
    printf("Highest fitness = %f (%d)\n", cdt_tab[0]->fitness, count);
    //printf("Fittest candidate = %d\n", count);
    count++;
  }
}

void saveCoefsToFile(char *path, AiCoefs coefs)
{
  FILE *f = fopen(path, "w");
  if (f == NULL)
  {
      printf("Error opening file!\n");
      exit(1);
  }
  fprintf(f,"%f\n%f\n%f\n%f\n", coefs.agg_height, coefs.holes, coefs.clears, coefs.bumpiness);


  fclose(f);
}
