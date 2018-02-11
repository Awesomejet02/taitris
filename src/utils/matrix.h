/**
 * @file    matrix.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   Matrix implement
 */

#ifndef TAITRIS_MATRIX_H
#define TAITRIS_MATRIX_H

#include <stdlib.h>
#include <assert.h>
#include <err.h>
#include <string.h>

/** Matrix structure */
struct matrix {
  size_t rows; /**< Rows */
  size_t cols; /**< Columns */
  double *data; /**< Values */
};

/**
 * Initialize the matrix
 *
 * @param mx a matrix
 * @param rows number of rows
 * @param cols number of columns
 *
 * @pre `mx` must be not NULL
 * @pre `rows` must be greater than zero
 * @pre `cols` must be greater than zero
 *
 * @post `mx` is size of `rows` rows and `cols` columns
 * @post `mx->data` is initialized with the right size
 *
 * @remarks Complexity: O(1)
 */
extern inline
void matrix_init(struct matrix *mx, size_t rows, size_t cols);

/**
 * Create a matrix of size `rows` rows and `cols` columns
 *
 * @param rows number of rows
 * @param cols number of columns
 *
 * @return the initialized matrix of size `rows` rows and `cols` columns
 *
 * @pre `rows` must be greater than zero
 * @pre `cols` must be greater than zero
 *
 * @remarks Complexity: O(1)
 */
extern inline
struct matrix *matrix_create(size_t rows, size_t cols);

/**
 * Free the matrix
 *
 * @param mx a matrix
 *
 * @pre `mx` must be not NULL
 * @pre `mx->data` must be not NULL
 *
 * @post `mx` is freed
 * @post `mx->data` is freed
 *
 * @remarks Complexity: O(1)
 */
extern inline
void matrix_free(struct matrix *mx);

/**
 * Get the number of rows
 *
 * @param mx a matrix
 * @return the number of rows
 *
 * @pre `mx` must be not NULL
 *
 * @remarks Complexity: O(1)
 */
extern inline
size_t matrix_rows(const struct matrix *mx);

/**
 * Get the number of columns
 *
 * @param mx a matrix
 * @return the number of columns
 *
 * @pre `mx` must be not NULL
 *
 * @remarks Complexity: O(1)
 */
extern inline
size_t matrix_cols(const struct matrix *mx);

/**
 * Get value at `rows` rows and `cols` columns
 *
 * @param mx a matrix
 * @param rows rows
 * @param cols columns
 * @return the value at `rows` rows and `cols` columns
 *
 * @pre `mx` must be not NULL
 * @pre `mx->data` must be not NULL
 * @pre `rows` must be between zero and `matrix_rows(mx)`
 * @pre `cols` must be between zero and `matrix_cols(mx)`
 *
 * @remarks Complexity: O(1)
 */
extern inline
double matrix_at(const struct matrix *mx, size_t rows, size_t cols);

/**
 * Set the value at `rows` rows and `cols` columns with `value`
 *
 * @param mx a matrix
 * @param rows rows
 * @param cols columns
 * @param value a value
 *
 * @pre `mx` must be not NULL
 * @pre `mx->data` must be not NULL
 * @pre `rows` must be between zero and `matrix_rows(mx)`
 * @pre `cols` must be between zero and `matrix_cols(mx)`
 *
 * @post the value at `rows` rows and `cols` columns is `value`
 *
 * @remarks Complexity: O(1)
 *
 */
extern inline
void matrix_set(struct matrix *mx, size_t rows, size_t cols, double value);

/**
 * Copy the matrix
 *
 * @param mx a matrix
 * @return the copy of `mx`
 *
 * @pre `mx` must be not NULL
 * @pre `mx->data` must be not NULL
 *
 * @remarks Complexity: O(1)
 */
extern inline
struct matrix *matrix_copy(const struct matrix *mx);

/**
 * Transpose the matrix
 *
 * @param mx a matrix
 * @return the transposed matrix
 *
 * @pre `mx` must be not NULL
 * @pre `mx->data` must be not NULL
 *
 * @remarks transposed matrix is size of `matrix_cols(mx)` rows and
 * `matrix_rows(mx)` columns
 * @remarks Complexity: O(N)
 */
struct matrix *matrix_transpose(const struct matrix *mx);

/**
 * Sum the matrix `mx1` with `mx2`
 *
 * @param mx1 a matrix
 * @param mx2 a matrix
 * @return the sum of `mx1` and `mx2`
 *
 * @pre `mx1` must be not NULL
 * @pre `mx1->data` must be not NULL
 * @pre `mx2` must be not NULL
 * @pre `mx2->data` must be not NULL
 * @pre `matrix_rows(mx1)` must be equal to `matrix_rows(mx2)`
 * @pre `matrix_cols(mx1)` must be equal to `matrix_cols(mx2)`
 *
 * @remarks Complexity: O(N)
 */
struct matrix *matrix_sum(const struct matrix *mx1, const struct matrix *mx2);

/**
 * Multiply the matrix `mx1` with `mx2`
 *
 * @param mx1 a matrix
 * @param mx2 a matrix
 * @return the product of `mx1` with `mx2`
 *
 * @pre `mx1` must be not NULL
 * @pre `mx1->data` must be not NULL
 * @pre `mx2` must be not NULL
 * @pre `mx2->data` must be not NULL
 * @pre `matrix_cols(mx1)` must be equal to `matrix_rows(mx2)`
 *
 * @remarks the result is a matrix of `matrix_rows(mx1)` rows and
 * `matrix_cols(mx2)` cols
 * @remarks Complexity: O(nmp)
 */
struct matrix *matrix_product(
    const struct matrix *mx1,
    const struct matrix *mx2
);

#endif //TAITRIS_MATRIX_H
