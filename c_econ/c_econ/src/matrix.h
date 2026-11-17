#ifndef MATRIX_H
#define MATRIX_H
#include <stddef.h>

/* ---------- STAGE 2: a tiny matrix toolkit ----------
 * Needed once you have more than one x. See LINALG_PRIMER.md first.
 * Store a rows x cols matrix as ONE flat array, row by row:
 *      element (i, j)  lives at  data[i * cols + j]
 */
typedef struct {
    int rows, cols;
    double *data;
} Matrix;

Matrix *mat_new(int rows, int cols);                 /* zero-filled; NULL on failure */
void    mat_free(Matrix *m);                         /* safe to call with NULL */
double  mat_get(const Matrix *m, int i, int j);
void    mat_set(Matrix *m, int i, int j, double v);

Matrix *mat_transpose(const Matrix *a);              /* new matrix, cols x rows */
Matrix *mat_multiply(const Matrix *a, const Matrix *b);  /* NULL if a->cols != b->rows */
Matrix *mat_inverse(const Matrix *a);                /* NULL if not square or singular */

void    mat_print(const Matrix *m);                  /* PROVIDED */

#endif
