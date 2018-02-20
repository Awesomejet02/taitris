/**
 * @file    score.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "score.h"

void computeScore(int *currentScore, int nbLine, int level) {
  switch (nbLine) {
    case 1:*currentScore += 40 * (level + 1);
      break;
    case 2:*currentScore += 100 * (level + 1);
      break;
    case 3:*currentScore += 300 * (level + 1);
      break;
    case 4:*currentScore += 1200 * (level + 1);
      break;
    default:break;
  }
}

void softDrop(int *currentScore) {
  *currentScore += 1;
}

void hardDrop(int *currentScore, int nbLine) {
  *currentScore += nbLine * 2;
}

void saveScore(tuple **scoreTab, char *name, int size, int score) {
  if (score >= scoreTab[9]->score) {
    tuple *newScore = malloc(sizeof(tuple));
    newScore->score = score;
    newScore->name = name;
    newScore->size = size;
    scoreTab[9] = newScore;

    int i = 8;
    while (i > 0 && score >= scoreTab[i]->score) {
      tuple *save = scoreTab[i];
      scoreTab[i] = scoreTab[i + 1];
      scoreTab[i + 1] = save;
    }

    FILE *file = fopen("data/score.txt", "w");
    if (file == NULL)
      errx(1, "error during fopen");

    for (int i = 0; i < 10; i++) {
      fwrite(&scoreTab[i]->size, sizeof(int), 1, file);
      fwrite(scoreTab[i]->name, 1, (size_t) scoreTab[i]->size, file);
      fwrite(&scoreTab[i]->score, sizeof(int), 1, file);
    }
    fclose(file);
  }
}

tuple **loadScore() {
  FILE *file = fopen("data/score.txt", "r");
  if (file == NULL)
    errx(1, "error during fopen");

  tuple **result = malloc(sizeof(tuple) * 10);

  int cpt = 0;
  while (cpt < 10) {
    int *size = malloc(sizeof(int));
    fread(size, sizeof(int), 1, file);
    char *name = malloc(sizeof(char) * *size);
    fread(name, sizeof(char), (size_t) *size, file);
    int *score = malloc(sizeof(int));
    fread(score, sizeof(int), 1, file);

    tuple *t = malloc(sizeof(tuple));
    t->size = *size;
    free(size);
    t->name = name;
    t->score = *score;
    free(score);
    result[cpt] = t;

    cpt++;
  }
  return result;
}

