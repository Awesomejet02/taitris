/**
 * @file    matrix.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   Matrix implement
 */

#ifndef TAITRIS_MATRIX_H
#define TAITRIS_MATRIX_H

#include <stdlib.h>
#include <stdio.h>
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
 * Create a matrix of size `rows` rows and `cols` columns from `values`
 *
 * @param rows number of rows
 * @param cols number of columns
 * @param values an array
 *
 * @return the initialized matrix of size `rows` rows and `cols` columns from
 * `values`
 *
 * @pre `rows` must be greater than zero
 * @pre `cols` must be greater than zero
 * @pre `values` must be not NULL
 *
 * @remarks Complexity: O(N)
 */
extern inline
struct matrix *matrix_create_from_array(
    size_t rows,
    size_t cols,
    const double values[]
);

/**
 * Free the matrix `mx`
 *
 * @param mx a matrix
 *
 * @pre `mx` must be not NULL
 *
 * @post `mx` is freed
 *
 * @remarks Complexity: O(1)
 */
extern inline
void matrix_free(struct matrix *mx);

/**
 * Get the number of rows `mx`
 *
 * @param mx a matrix
 * @return the number of rows of `mx`
 *
 * @pre `mx` must be not NULL
 *
 * @remarks Complexity: O(1)
 */
extern inline
size_t matrix_rows(const struct matrix *mx);

/**
 * Get the number of columns of `mx`
 *
 * @param mx a matrix
 * @return the number of columns `mx`
 *
 * @pre `mx` must be not NULL
 *
 * @remarks Complexity: O(1)
 */
extern inline
size_t matrix_cols(const struct matrix *mx);

/**
 * Get value at `rows` rows and `cols` columns of `mx`
 *
 * @param mx a matrix
 * @param rows rows
 * @param cols columns
 * @return the value at `rows` rows and `cols` columns of `mx`
 *
 * @pre `mx` must be not NULL
 * @pre `rows` must be between `[0, matrix_rows(mx)[`
 * @pre `cols` must be between `[0, matrix_cols(mx)[`
 *
 * @remarks Complexity: O(1)
 */
extern inline
double matrix_at(const struct matrix *mx, size_t rows, size_t cols);

/**
 * Set the value at `rows` rows and `cols` columns with `value` of `mx`
 *
 * @param mx a matrix
 * @param rows rows
 * @param cols columns
 * @param value a value
 *
 * @pre `mx` must be not NULL
 * @pre `rows` must be between `[0, matrix_rows(mx)[`
 * @pre `cols` must be between `[0, matrix_cols(mx)[`
 *
 * @post the value at `rows` rows and `cols` columns is `value`
 *
 * @remarks Complexity: O(1)
 *
 */
extern inline
void matrix_set(struct matrix *mx, size_t rows, size_t cols, double value);

/**
 * Copy the matrix `mx`
 *
 * @param mx a matrix
 * @return the copy of `mx`
 *
 * @pre `mx` must be not NULL
 *
 * @remarks Complexity: O(1)
 */
extern inline
struct matrix *matrix_copy(const struct matrix *mx);

/**
 * Transpose the matrix `mx`
 *
 * @param mx a matrix
 * @param tmx a matrix
 *
 * @pre `mx` must be not NULL
 * @pre `tmx` must be not NULL
 * @pre `tmx` must be not equal to `mx`
 * @pre `matrix_rows(tmx)` must be equal to `matrix_cols(mx)`
 * @pre `matrix_cols(tmx)` must be equal to `matrix_rows(mx)`
 *
 * @post `tmx` is the transposed matrix of `mx`
 *
 * @remarks Complexity: O(N)
 */
void matrix_transpose(const struct matrix *mx, struct matrix *tmx);

/**
 * Sum the matrix `mx1` with `mx2`
 *
 * @param mx1 a matrix
 * @param mx2 a matrix
 * @param sum a matrix
 *
 * @pre `mx1` must be not NULL
 * @pre `mx2` must be not NULL
 * @pre `sum` must be not NULL
 * @pre `matrix_rows(mx1)` must be equal to `matrix_rows(mx2)`
 * @pre `matrix_cols(mx1)` must be equal to `matrix_cols(mx2)`
 * @pre `matrix_rows(sum)` must be equal to `matrix_rows(mx1)`
 * @pre `matrix_cols(sum)` must be equal to `matrix_cols(mx1)`
 *
 * @post `sum` is the sum of matrix `mx1` with `mx2`
 *
 * @remarks Complexity: O(N)
 */
void matrix_sum(
    const struct matrix *mx1,
    const struct matrix *mx2,
    struct matrix *sum
);

/**
 * Do the hadamard product of matrix `mx1` with `mx2`
 *
 * @param mx1 a matrix
 * @param mx2 a matrix
 * @param prod a matrix
 *
 * @pre `mx1` must be not NULL
 * @pre `mx2` must be not NULL
 * @pre `prod` must be not NULL
 * @pre `matrix_rows(mx1)` must be equal to `matrix_rows(mx2)`
 * @pre `matrix_cols(mx1)` must be equal to `matrix_cols(mx2)`
 * @pre `matrix_rows(prod)` must be equal to `matrix_rows(mx1)`
 * @pre `matrix_cols(prod)` must be equal to `matrix_cols(mx1)`
 *
 * @post `prod` is the hadamard product of matrix `mx1` with `mx2`
 *
 * @remarks Complexity: O(N)
 */
void matrix_hadamard_product(
    const struct matrix *mx1,
    const struct matrix *mx2,
    struct matrix *prod
);

/**
 * Multiply the matrix `mx1` with `mx2`
 *
 * @param mx1 a matrix
 * @param mx2 a matrix
 * @param prod a matrix
 *
 * @pre `mx1` must be not NULL
 * @pre `mx2` must be not NULL
 * @pre `prod` must be not NULL
 * @pre `prod` must be not equal to `mx1`
 * @pre `prod` must be not equal to `mx2`
 * @pre `matrix_cols(mx1)` must be equal to `matrix_rows(mx2)`
 * @pre `matrix_rows(prod)` must be equal to `matrix_rows(mx1)`
 * @pre `matrix_cols(prod)` must be equal to `matrix_cols(mx2)`
 *
 * @post `prod` is the product of `mx1` with `mx2`
 *
 * @remarks Complexity: O(nmp)
 */
void matrix_product(
    const struct matrix *mx1,
    const struct matrix *mx2,
    struct matrix *prod
);

/**
 * Scale the matrix `mx` with `scale`
 *
 * @param mx a matrix
 * @param scale the scale factor
 * @param smx a matrix
 *
 * @pre `mx` must be not NULL
 * @pre `smx` must be not NULL
 * @pre `matrix_rows(smx)` must be equal to `matrix_rows(mx)`
 * @pre `matrix_cols(smx)` must be equal to `matrix_cols(mx)`
 *
 * @post `smx` is the `scale` scaled matrix of `mx`
 *
 * @remarks Complexity: O(N)
 */
void matrix_scale(const struct matrix *mx, double scale, struct matrix *smx);

/**
 * Do the dot product of vector `v1` with vector `v2`
 *
 * @param v1 a vector
 * @param v2 a vector
 * @return the dot product of vector `v1` with vector `v2`
 *
 * @pre `v1` must be not NULL
 * @pre `v2` must be not NULL
 * @pre `matrix_cols(v1)` and `matrix_cols(v2)` must be equal to one
 * @pre `matrix_rows(v1)` must be equal to `matrix_rows(v2)`
 *
 * @remarks Complexity: O(N)
 */
double matrix_dot_product(const struct matrix *v1, const struct matrix *v2);

/**
 * Set the matrix `mx` to an identity matrix
 *
 * @param mx a matrix
 *
 * @pre `mx` must be not NULL
 * @pre `matrix_rows(mx)` must be equal to `matrix_cols(mx)`
 *
 * @post `mx` is an identity matrix
 *
 * @remarks Complexity: O(N)
 */
void matrix_identity(struct matrix *mx);

/**
 * Check if the matrix `mx` is squared
 *
 * @param mx a matrix
 * @return `1` if the matrix is squared, `0` otherwise
 *
 * @pre `mx` must be not NULL
 *
 * @remarks Complexity: O(1)
 */
extern inline
int matrix_is_square(const struct matrix *mx);

/**
 * Check if the matrix `mx` is diagonaled
 *
 * @param mx a matrix
 * @return `1` if the matrix is diagonaled, `0` otherwise
 *
 * @pre `mx` must be not NULL
 *
 * @remarks Complexity: O(N)
 */
extern inline
int matrix_is_diagonal(const struct matrix *mx);

/**
 * Check if the matrix `mx` is upper triangulared
 *
 * @param mx a matrix
 * @return `1` if the matrix is upper triangulared, `0` otherwise
 *
 * @pre `mx` must be not NULL
 *
 * @remarks Complexity: O(N)
 */
extern inline
int matrix_is_upper_triangulared(const struct matrix *mx);

/**
 * Take a vector `v` and put it to the diagonal of `mx`
 *
 * @param v a vector
 * @param mx a matrix
 *
 * @pre `v` must be not NULL
 * @pre `mx` must be not NULL
 * @pre `matrix_cols(v)` must be equal to one
 * @pre `matrix_rows(v)` must be equel to `matrix_rows(mx)`
 * @pre `matrix_rows(mx)` must be equel to `matrix_cols(mx)`
 *
 * @post The diagonal of `mx` is `v`
 */
void matrix_diagonal(const struct matrix *v, struct matrix *mx);

/**
 * Print the matrix `mx`
 *
 * @param mx a matrix
 *
 * @pre `mx` must be not NULL
 *
 * @post Print the matrix `mx`
 */
void matrix_print(const struct matrix *mx);

#endif //TAITRIS_MATRIX_H
