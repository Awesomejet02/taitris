/**
 * @file    random.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "random.h"

int *generateRandom(int size, int cache) {
  int *tab = malloc(sizeof(int) * cache);
  for (int i = 0; i < cache; i++)
    tab[i] = i % size;

  shuffle(tab);

  return tab;
}

void swap(int *tab, int a, int b) {
  int save = tab[a];
  tab[a] = tab[b];
  tab[b] = save;
}

void shuffle(int *tab) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  srandom((unsigned int) (ts.tv_nsec ^ ts.tv_sec));

  int r;
  for (int i = 0; i < 70; i++) {
    r = i + (int) (random() % (70 - i));
    swap(tab, i, r);
  }
}

int getRandom() {
  static int index = -1;
  static int *data = NULL;

  if (index < 0 || index >= 70) {
    data = generateRandom(1, 70);
    index = 0;
  }

  return data[index++];
}