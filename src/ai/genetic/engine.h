//
// Created by dotty on 2/22/18.
//

#ifndef TAITRIS_ENGINE_H
#define TAITRIS_ENGINE_H

#include "tools.h"

struct ai_coefs {
    double agg_height;
    double holes;
    double clears;
    double bumpiness;
    //double tetris;
    //double blockades;
};

extern
struct ai_coefs *get_coefs();

extern
double get_rank(struct board *brd);
#endif //TAITRIS_ENGINE_H
