/**
 * @file    piece_queue.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Piece queue
 */
#include "piece_queue.h"

PieceQueue *piece_queue_create() {
  PieceQueue *q = malloc(sizeof(PieceQueue));

  if (q == NULL)
    errx(EXIT_FAILURE, "Can't create piece queue structure");

  memset(q, 0, sizeof(PieceQueue));

  q->length = PIECE_QUEUE_LENGTH;
  q->data = malloc(q->length * sizeof(PieceType));

  if (q->data == NULL)
    errx(EXIT_FAILURE, "Can't create piece queue data of length %zu",
         q->length);

  memset(q->data, 0, q->length * sizeof(PieceType));

  piece_queue_fill_data(q->data, q->length);

  return q;
}

void piece_queue_free(PieceQueue *q) {
  assert(q != NULL);

  free(q->data);
  free(q);
}

void piece_queue_fill_data(PieceType *data, size_t length) {
  assert(data != NULL);

  for (size_t i = 0; i < length; i++)
    *(data + i) = seven_bag_draw();
}

void piece_queue_extend(PieceQueue *q) {
  assert(q != NULL);

  size_t newLength = q->length + PIECE_QUEUE_LENGTH;

  PieceType *newData = malloc(newLength * sizeof(PieceType));

  if (newData == NULL)
    errx(EXIT_FAILURE, "Can't extend piece queue data of length %zu",
         newLength);

  memset(newData, 0, newLength * sizeof(PieceType));
  memcpy(newData, q->data, q->length);

  piece_queue_fill_data(newData + q->length, PIECE_QUEUE_LENGTH);

  free(q->data);

  q->data = newData;
  q->length = newLength;
}

PieceType piece_queue_get(PieceQueue *q, size_t index) {
  assert(q != NULL);

  while (index >= q->length)
    piece_queue_extend(q);

  return *(q->data + index);
}