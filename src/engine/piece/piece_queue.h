/**
 * @file    piece_queue.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Piece queue
 */
#ifndef TAITRIS_PIECE_QUEUE_H
#define TAITRIS_PIECE_QUEUE_H

#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <assert.h>

#include "piece_type.h"
#include "seven_bag.h"
#include "../../utils/random.h"

#define PIECE_QUEUE_LENGTH 5

typedef struct {
  unsigned int seed;
  size_t length;

  PieceType *data;
} PieceQueue;

PieceQueue *piece_queue_create(unsigned int seed);
void piece_queue_free(PieceQueue *q);
void piece_queue_fill_data(PieceType *data, size_t length);
void piece_queue_extend(PieceQueue *q);
PieceType piece_queue_get(PieceQueue *q, size_t index);

#endif //TAITRIS_PIECE_QUEUE_H
