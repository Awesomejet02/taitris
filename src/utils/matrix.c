/**
 * @file    matrix.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   Matrix implement
 */

#include "matrix.h"

struct matrix *matrix_create(size_t rows, size_t cols) {
  assert(rows > 0);
  assert(cols > 0);

  struct matrix *mx = malloc(sizeof(struct matrix));

  if (mx == NULL)
    errx(
        EXIT_FAILURE,
        "Matrix initialization of size %zu rows and %zu columns failed",
        rows,
        cols
    );

  memset(mx, 0, sizeof(struct matrix));

  mx->rows = rows;
  mx->cols = cols;
  mx->data = calloc(rows * cols, sizeof(double));

  if (mx->data == NULL)
    errx(
        EXIT_FAILURE,
        "Matrix data initialization of size %zu rows and %zu columns failed",
        rows,
        cols
    );

  return mx;
}

struct matrix *matrix_create_from_array(
    size_t rows,
    size_t cols,
    const double values[]
) {
  assert(rows > 0);
  assert(cols > 0);
  assert(values != NULL);

  struct matrix *mx = malloc(sizeof(struct matrix));

  if (mx == NULL)
    errx(
        EXIT_FAILURE,
        "Matrix initialization of size %zu rows and %zu columns failed",
        rows,
        cols
    );

  memset(mx, 0, sizeof(struct matrix));

  mx->rows = rows;
  mx->cols = cols;
  mx->data = calloc(rows * cols, sizeof(double));

  if (mx->data == NULL)
    errx(
        EXIT_FAILURE,
        "Matrix data initialization of size %zu rows and %zu columns failed",
        rows,
        cols
    );

  memcpy(mx->data, values, rows * cols * sizeof(double));

  return mx;
}

void matrix_free(struct matrix *mx) {
  assert(mx != NULL);

  free(mx->data);
  free(mx);
}

size_t matrix_rows(const struct matrix *mx) {
  assert(mx != NULL);

  return mx->rows;
}

size_t matrix_cols(const struct matrix *mx) {
  assert(mx != NULL);

  return mx->cols;
}

double matrix_at(const struct matrix *mx, size_t rows, size_t cols) {
  assert(mx != NULL);
  assert(rows < mx->rows);
  assert(cols < mx->cols);

  return *(mx->data + cols * mx->rows + rows);
}

void matrix_set(struct matrix *mx, size_t rows, size_t cols, double value) {
  assert(mx != NULL);
  assert(rows < mx->rows);
  assert(cols < mx->cols);

  *(mx->data + cols * mx->rows + rows) = value;
}

struct matrix *matrix_copy(const struct matrix *mx) {
  assert(mx != NULL);

  struct matrix *cp = matrix_create(mx->rows, mx->cols);
  memcpy(cp->data, mx->data, cp->rows * cp->cols * sizeof(double));

  return cp;
}

void matrix_transpose(const struct matrix *mx, struct matrix *tmx) {
  assert(mx != NULL);
  assert(tmx != NULL);
  assert(tmx != mx);
  assert(tmx->rows == mx->cols);
  assert(tmx->cols == mx->rows);

  for (size_t i = 0; i < mx->rows; i++)
    for (size_t j = 0; j < mx->cols; j++)
      matrix_set(tmx, j, i, matrix_at(mx, i, j));
}

void matrix_sum(
    const struct matrix *mx1,
    const struct matrix *mx2,
    struct matrix *sum
) {
  assert(mx1 != NULL);
  assert(mx2 != NULL);
  assert(sum != NULL);
  assert(mx1->rows == mx2->rows);
  assert(mx1->cols == mx2->cols);
  assert(sum->rows == mx1->rows);
  assert(sum->cols == mx1->cols);

  for (size_t i = 0; i < sum->rows; i++)
    for (size_t j = 0; j < sum->cols; j++)
      matrix_set(sum, i, j, matrix_at(mx1, i, j) + matrix_at(mx2, i, j));
}

void matrix_hadamard_product(
    const struct matrix *mx1,
    const struct matrix *mx2,
    struct matrix *prod
) {
  assert(mx1 != NULL);
  assert(mx2 != NULL);
  assert(prod != NULL);
  assert(mx1->rows == mx2->rows);
  assert(mx1->cols == mx2->cols);
  assert(prod->rows == mx1->rows);
  assert(prod->cols == mx1->cols);

  for (size_t i = 0; i < prod->rows; i++)
    for (size_t j = 0; j < prod->cols; j++)
      matrix_set(prod, i, j, matrix_at(mx1, i, j) * matrix_at(mx2, i, j));
}

void matrix_product(
    const struct matrix *mx1,
    const struct matrix *mx2,
    struct matrix *prod
) {
  assert(mx1 != NULL);
  assert(mx2 != NULL);
  assert(prod != NULL);
  assert(prod != mx1);
  assert(prod != mx2);
  assert(mx1->cols == mx2->rows);
  assert(prod->rows == mx1->rows);
  assert(prod->cols == mx2->cols);

  for (size_t i = 0; i < prod->rows; i++) {
    for (size_t j = 0; j < prod->cols; j++) {
      double val = 0;

      for (size_t k = 0; k < mx1->cols; k++)
        val += matrix_at(mx1, i, k) * matrix_at(mx2, k, j);

      matrix_set(prod, i, j, val);
    }
  }
}

void matrix_scale(const struct matrix *mx, double scale, struct matrix *smx) {
  assert(mx != NULL);
  assert(smx != NULL);
  assert(smx->rows == mx->rows);
  assert(smx->cols == mx->cols);

  for (size_t i = 0; i < smx->rows; i++)
    for (size_t j = 0; j < smx->cols; j++)
      matrix_set(smx, i, j, matrix_at(mx, i, j) * scale);
}

double matrix_dot_product(const struct matrix *v1, const struct matrix *v2) {
  assert(v1 != NULL);
  assert(v2 != NULL);
  assert(v1->cols == 1);
  assert(v2->cols == 1);
  assert(v1->rows == v2->rows);

  double prod = 0;

  for (size_t i = 0; i < v1->rows; i++)
    prod += matrix_at(v1, i, 1) * matrix_at(v2, i, 1);

  return 0;
}

void matrix_identity(struct matrix *mx) {
  assert(mx != NULL);
  assert(mx->rows == mx->cols);

  for (size_t i = 0; i < mx->rows; i++)
    for (size_t j = 0; j < mx->cols; j++)
      if (i == j)
        matrix_set(mx, i, j, 1);
      else
        matrix_set(mx, i, j, 0);
}

int matrix_is_square(const struct matrix *mx) {
  assert(mx != NULL);

  return mx->rows == mx->cols;
}

int matrix_is_diagonal(const struct matrix *mx) {
  assert(mx != NULL);

  if (mx->cols != mx->rows) return 0;

  for (size_t i = 0; i < mx->rows; i++)
    for (size_t j = 0; j < mx->cols; j++)
      if (i != j && matrix_at(mx, i, j) != 0)
        return 0;

  return 1;
}

int matrix_is_upper_triangulared(const struct matrix *mx) {
  assert(mx != NULL);

  if (mx->cols != mx->rows) return 0;

  for (size_t j = 0; j < mx->cols; j++)
    for (size_t i = j + 1; i < mx->rows; i++)
      if (matrix_at(mx, i, j) != 0)
        return 0;

  return 1;
}

void matrix_diagonal(const struct matrix *v, struct matrix *mx) {
  assert(v != NULL);
  assert(mx != NULL);
  assert(v->cols == 1);
  assert(v->rows == mx->rows);
  assert(mx->rows == mx->cols);

  for (size_t i = 0; i < mx->rows; i++)
    for (size_t j = 0; j < mx->cols; j++)
      if (i == j)
        matrix_set(mx, i, j, matrix_at(v, i, 1));
      else
        matrix_set(mx, i, j, 0);
}

void matrix_print(const struct matrix *mx) {
  assert(mx != NULL);

  printf("\n");
  for (size_t i = 0; i < mx->rows; i++) {
    for (size_t j = 0; j < mx->cols; j++) {
      printf("% 6.2f ", matrix_at(mx, i, j));
    }
    printf("\n");
  }
  printf("\n");

}