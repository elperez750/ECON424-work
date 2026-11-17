#ifndef OLS_H
#define OLS_H
#include "matrix.h"

/* ---------- STAGE 3: OLS with any number of regressors ----------
 * NOTE: k here = number of coefficients INCLUDING the intercept (= columns of X).
 * Wooldridge's k excludes the intercept, so his k = this k - 1.  df = n - k.
 */
typedef struct {
    int n, k, df;
    double *beta;       /* length k */
    double *se;         /* length k */
    double *t;          /* length k */
    double *p;          /* length k, two-sided */
    double *fitted;     /* length n */
    double *resid;      /* length n */
    double sst, sse, ssr;
    double r2, adj_r2;
    double sigma_hat;
    double f_stat, f_p; /* overall F test: all slopes = 0 */
    Matrix *xtx_inv;    /* (X'X)^-1, kept so predictions can reuse it */
} OLS;

/* Build X: a column of 1s followed by each of the ncols columns given (each length n). */
Matrix *design_matrix(int n, int ncols, const double *cols[]);

/* Fit y on X (X must already include the intercept column). NULL on failure
 * (e.g. singular X'X from perfectly collinear columns). Allocate every pointer
 * field above with malloc/calloc so ols_free() can release them. */
OLS *ols_fit(const Matrix *X, const double *y);

void ols_free(OLS *m);       /* PROVIDED */

#endif
