#include "check.h"
#include "csv.h"
#include "ols.h"
#include "expected.h"

int main(void) {
    printf("=== Stage 3: OLS with several regressors ===\n");

    printf("-- tiny example x=(2,4,6), y=(3,5,10) through the general code\n");
    double tx[] = {2, 4, 6}, ty[] = {3, 5, 10};
    const double *tcols[] = {tx};
    Matrix *TX = design_matrix(3, 1, tcols);
    check_true("design_matrix is 3x2 with a column of 1s",
               TX && TX->rows == 3 && TX->cols == 2 && mat_get(TX, 0, 0) == 1.0
               && mat_get(TX, 2, 1) == 6.0);
    OLS *t = TX ? ols_fit(TX, ty) : NULL;
    if (!t) { check_true("ols_fit returned a model", 0); }
    else {
        check_near("beta0 = -1",      t->beta[0], -1.0, 1e-9);
        check_near("beta1 = 1.75",    t->beta[1], 1.75, 1e-9);
        check_near("SSR = 1.5",       t->ssr, 1.5, 1e-9);
        check_near("df = 1",          t->df, 1, 1e-12);
        check_near("sigma_hat",       t->sigma_hat, 1.224744871391589, 1e-9);
        check_near("se(beta1)",       t->se[1], 0.4330127018922193, 1e-9);
        check_near("R^2",             t->r2, 24.5 / 26.0, 1e-9);
    }
    ols_free(t); mat_free(TX);

    printf("-- lwage on educ and exper (30 rows)\n");
    Dataset *ds = dataset_load("data/sample30.csv");
    if (!ds) { printf("Could not open data/sample30.csv (run from the project root).\n"); return 1; }
    int n = ds->nrows;
    const double *cols[] = {dataset_col(ds, "educ"), dataset_col(ds, "exper")};
    Matrix *X = design_matrix(n, 2, cols);
    OLS *m = X ? ols_fit(X, dataset_col(ds, "lwage")) : NULL;
    if (!m) { check_true("ols_fit returned a model", 0); }
    else {
        double b[]  = {E2_B0, E2_B1, E2_B2},  se[] = {E2_SE0, E2_SE1, E2_SE2};
        double t_[] = {E2_T0, E2_T1, E2_T2},  p[]  = {E2_P0, E2_P1, E2_P2};
        const char *nm[] = {"intercept", "educ", "exper"};
        char label[64];
        for (int j = 0; j < 3; j++) {
            snprintf(label, sizeof label, "beta  (%s)", nm[j]); check_near(label, m->beta[j], b[j], 1e-8);
            snprintf(label, sizeof label, "se    (%s)", nm[j]); check_near(label, m->se[j], se[j], 1e-8);
            snprintf(label, sizeof label, "t     (%s)", nm[j]); check_near(label, m->t[j], t_[j], 1e-6);
            snprintf(label, sizeof label, "p     (%s)", nm[j]); check_near(label, m->p[j], p[j], 1e-9);
        }
        check_near("SSR",          m->ssr, E2_SSR, 1e-8);
        check_near("R^2",          m->r2, E2_R2, 1e-9);
        check_near("adjusted R^2", m->adj_r2, E2_ADJR2, 1e-9);
        check_near("sigma_hat",    m->sigma_hat, E2_SIGMA, 1e-9);
        check_near("overall F",    m->f_stat, E2_F, 1e-6);
        check_near("overall F p-value", m->f_p, E2_FP, 1e-9);
        check_near("SST = SSE + SSR", m->sst, m->sse + m->ssr, 1e-9);
        double rs = 0.0;
        for (int i = 0; i < n; i++) rs += m->resid[i];
        check_near("residuals sum to ~0", rs, 0.0, 1e-9);
        check_near("fitted + resid = y (row 0)", m->fitted[0] + m->resid[0], dataset_col(ds, "lwage")[0], 1e-9);
    }
    ols_free(m); mat_free(X); dataset_free(ds);
    return check_summary();
}
