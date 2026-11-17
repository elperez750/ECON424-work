#include <stdlib.h>
#include <math.h>
#include "ols.h"
#include "dist.h"

Matrix *design_matrix(int n, int ncols, const double *cols[]) {
    /* TODO: n x (ncols+1) matrix. Column 0 is all 1s; column j+1 is cols[j]. */
    return NULL;
}

OLS *ols_fit(const Matrix *X, const double *y) {
    /* TODO, in this order:
     *  1. n = X->rows, k = X->cols, df = n - k
     *  2. XtX = X' X     Xty = X' y (treat y as an n x 1 matrix)
     *  3. xtx_inv = inverse(XtX)      -> NULL if singular, return NULL
     *  4. beta = xtx_inv * Xty
     *  5. fitted_i = sum_j X(i,j) * beta_j        resid_i = y_i - fitted_i
     *  6. SSR = sum resid^2   SST = sum (y - ybar)^2   SSE = SST - SSR
     *     r2 = 1 - SSR/SST   adj_r2 = 1 - (1 - r2)(n - 1)/(n - k)
     *  7. sigma_hat = sqrt(SSR / df)
     *  8. se_j = sigma_hat * sqrt( xtx_inv(j, j) )   t_j = beta_j / se_j
     *     p_j = t_pvalue_two_sided(t_j, df)
     *  9. F = (SSE / (k - 1)) / (SSR / df)     f_p = f_pvalue(F, k - 1, df)
     */
    return NULL;
}

void ols_free(OLS *m) {
    if (!m) return;
    free(m->beta); free(m->se); free(m->t); free(m->p);
    free(m->fitted); free(m->resid);
    mat_free(m->xtx_inv);
    free(m);
}
