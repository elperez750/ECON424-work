#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

/* TODO: implement the functions marked TODO. Read LINALG_PRIMER.md first. */

Matrix *mat_new(int rows, int cols) {
    /* TODO: malloc the struct, calloc rows*cols doubles, set rows/cols.
     * Return NULL if either allocation fails (free the struct if only the 2nd fails). */
    return NULL;
}

void mat_free(Matrix *m) {
    /* TODO: free m->data, then free m. Do nothing if m is NULL. */
}

double mat_get(const Matrix *m, int i, int j) {
    /* TODO: return the element at row i, column j */
    return NAN;
}

void mat_set(Matrix *m, int i, int j, double v) {
    /* TODO: store v at row i, column j */
}

Matrix *mat_transpose(const Matrix *a) {
    /* TODO: result (j, i) = a (i, j) */
    return NULL;
}

Matrix *mat_multiply(const Matrix *a, const Matrix *b) {
    /* TODO: if a->cols != b->rows return NULL.
     * result(i, j) = sum over k of a(i, k) * b(k, j)   (three nested loops) */
    return NULL;
}

Matrix *mat_inverse(const Matrix *a) {
    /* TODO: Gauss-Jordan elimination.
     *  1. If a is not square return NULL.
     *  2. Build an n x 2n working array [ A | I ].
     *  3. For each column c:
     *       - find the row at or below c with the largest |value| in column c
     *         (partial pivoting); if that value is ~0 (say < 1e-12) the matrix is
     *         singular -> free everything and return NULL
     *       - swap that row into position c
     *       - divide row c by its pivot so the pivot becomes 1
     *       - subtract multiples of row c from every OTHER row so column c is 0 there
     *  4. The right half now holds the inverse. Copy it into a new Matrix. */
    return NULL;
}

void mat_print(const Matrix *m) {
    if (!m) { printf("(null matrix)\n"); return; }
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) printf("%12.6f ", m->data[i * m->cols + j]);
        printf("\n");
    }
}
