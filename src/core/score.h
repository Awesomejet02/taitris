/**
 * @file    score.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#ifndef TAITRIS_SCORE_H
#define TAITRIS_SCORE_H

#include <stdlib.h>
#include <err.h>
#include <stdio.h>
#include "game.h"

void computeScore(int *currentScore, int nbline, int level);

void softDrop(int *currentScore);

void hardDrop(int *currentScore, int nbLine);

struct s_tuple {
  char *name;
  int size;
  int score;
};
typedef struct s_tuple tuple;

void saveScore(tuple **scoreTab, char *name, int size, int score);

tuple **loadScore();

#endif //TAITRIS_SCORE_H
