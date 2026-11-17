#include <stdlib.h>
#include "check.h"
#include "matrix.h"

static Matrix *make(int r, int c, const double *v) {
    Matrix *m = mat_new(r, c);
    if (!m) return NULL;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) mat_set(m, i, j, v[i * c + j]);
    return m;
}

static int close_to(const Matrix *m, int r, int c, const double *v, double tol) {
    if (!m || m->rows != r || m->cols != c) return 0;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if (!(fabs(mat_get(m, i, j) - v[i * c + j]) <= tol)) return 0;
    return 1;
}

int main(void) {
    printf("=== Stage 2: matrix toolkit ===\n");
    Matrix *z = mat_new(2, 3);
    check_true("mat_new gives a 2x3 matrix", z && z->rows == 2 && z->cols == 3);
    check_true("mat_new is zero-filled", z && mat_get(z, 1, 2) == 0.0);
    if (z) { mat_set(z, 1, 2, 7.5); check_near("set then get", mat_get(z, 1, 2), 7.5, 1e-12); }
    mat_free(z);
    mat_free(NULL);   /* must not crash */

    double xv[] = {1, 2, 1, 4, 1, 6};          /* the design matrix from the workbook */
    double yv[] = {3, 5, 10};
    Matrix *X = make(3, 2, xv), *y = make(3, 1, yv);

    Matrix *Xt = X ? mat_transpose(X) : NULL;
    double xt_want[] = {1, 1, 1, 2, 4, 6};
    check_true("transpose of X is 2x3 [1 1 1; 2 4 6]", close_to(Xt, 2, 3, xt_want, 1e-12));

    Matrix *XtX = (Xt && X) ? mat_multiply(Xt, X) : NULL;
    double xtx_want[] = {3, 12, 12, 56};
    check_true("X'X = [3 12; 12 56]", close_to(XtX, 2, 2, xtx_want, 1e-12));

    Matrix *Xty = (Xt && y) ? mat_multiply(Xt, y) : NULL;
    double xty_want[] = {18, 86};
    check_true("X'y = [18; 86]", close_to(Xty, 2, 1, xty_want, 1e-12));

    check_true("multiply with mismatched sizes returns NULL", X && mat_multiply(X, X) == NULL);

    Matrix *inv = XtX ? mat_inverse(XtX) : NULL;
    double inv_want[] = {56.0 / 24, -12.0 / 24, -12.0 / 24, 3.0 / 24};
    check_true("inverse of X'X = (1/24)[56 -12; -12 3]", close_to(inv, 2, 2, inv_want, 1e-9));

    Matrix *prod = (XtX && inv) ? mat_multiply(XtX, inv) : NULL;
    double id[] = {1, 0, 0, 1};
    check_true("A * A^-1 = identity", close_to(prod, 2, 2, id, 1e-9));

    Matrix *beta = (inv && Xty) ? mat_multiply(inv, Xty) : NULL;
    double beta_want[] = {-1.0, 1.75};
    check_true("(X'X)^-1 X'y = [-1; 1.75]   (OLS by matrices!)", close_to(beta, 2, 1, beta_want, 1e-9));

    double sv[] = {1, 2, 2, 4};                 /* second row = 2 * first row */
    Matrix *S = make(2, 2, sv);
    check_true("singular matrix [1 2; 2 4] -> NULL", S && mat_inverse(S) == NULL);

    double tv[] = {2, 1, 1, 3, 2, 1, 1, 1, 4};  /* needs row swaps / general case */
    Matrix *T = make(3, 3, tv);
    Matrix *Ti = T ? mat_inverse(T) : NULL;
    Matrix *Tp = (T && Ti) ? mat_multiply(T, Ti) : NULL;
    double id3[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    check_true("3x3 inverse: T * T^-1 = identity", close_to(Tp, 3, 3, id3, 1e-9));

    double pv[] = {0, 1, 1, 0};                 /* zero on the diagonal: needs pivoting */
    Matrix *P = make(2, 2, pv);
    Matrix *Pi = P ? mat_inverse(P) : NULL;
    check_true("pivoting: inverse of [0 1; 1 0]", close_to(Pi, 2, 2, pv, 1e-12));

    mat_free(X); mat_free(y); mat_free(Xt); mat_free(XtX); mat_free(Xty); mat_free(inv);
    mat_free(prod); mat_free(beta); mat_free(S); mat_free(T); mat_free(Ti); mat_free(Tp);
    mat_free(P); mat_free(Pi);
    return check_summary();
}
