#include "matrix.h"

void matrix_init(struct matrix *mx, size_t rows, size_t cols) {
  assert(mx != NULL);
  assert(rows > 0);
  assert(cols > 0);

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
}

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

  matrix_init(mx, rows, cols);

  return mx;
}

void matrix_free(struct matrix *mx) {
  assert(mx != NULL);
  assert(mx->data != NULL);

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
  assert(mx->data != NULL);
  assert(rows >= 0 && rows < mx->rows);
  assert(cols >= 0 && cols < mx->cols);

  return *(mx->data + cols * mx->rows + rows);
}

void matrix_set(struct matrix *mx, size_t rows, size_t cols, double value) {
  assert(mx != NULL);
  assert(mx->data != NULL);
  assert(rows >= 0 && rows < mx->rows);
  assert(cols >= 0 && cols < mx->cols);

  *(mx->data + cols * mx->rows + rows) = value;
}

struct matrix *matrix_copy(const struct matrix *mx) {
  assert(mx != NULL);
  assert(mx->data != NULL);

  struct matrix *cp = matrix_create(mx->rows, mx->cols);
  memcpy(cp->data, mx->data, cp->rows * cp->cols * sizeof(double));

  return cp;
}

struct matrix *matrix_transpose(const struct matrix *mx) {
  assert(mx != NULL);
  assert(mx->data != NULL);

  struct matrix *tmx = matrix_create(mx->cols, mx->rows);

  for (size_t i = 0; i < mx->rows; i++)
    for (size_t j = 0; j < mx->cols; j++)
      matrix_set(tmx, j, i, matrix_at(mx, i, j));

  return tmx;
}

struct matrix *matrix_sum(const struct matrix *mx1, const struct matrix *mx2) {
  assert(mx1 != NULL);
  assert(mx1->data != NULL);
  assert(mx2 != NULL);
  assert(mx2->data != NULL);
  assert(mx1->rows == mx2->rows);
  assert(mx1->cols == mx2->cols);

  struct matrix *sum = matrix_create(mx1->rows, mx1->cols);

  for (size_t i = 0; i < mx1->rows; i++)
    for (size_t j = 0; j < mx1->cols; j++)
      matrix_set(sum, i, j, matrix_at(mx1, i, j) + matrix_at(mx2, i, j));

  return sum;
}

struct matrix *matrix_product(
    const struct matrix *mx1,
    const struct matrix *mx2
) {
  assert(mx1 != NULL);
  assert(mx1->data != NULL);
  assert(mx2 != NULL);
  assert(mx2->data != NULL);
  assert(mx1->cols == mx2->rows);

  struct matrix *prod = matrix_create(mx1->rows, mx2->cols);

  for (size_t i = 0; i < mx1->rows; i++) {
    for (size_t j = 0; j < mx2->cols; j++) {
      double val = 0;

      for (size_t k = 0; k < mx1->cols; k++)
        val += matrix_at(mx1, i, k) * matrix_at(mx2, k, j);

      matrix_set(prod, i, j, val);
    }
  }

  return prod;
}
