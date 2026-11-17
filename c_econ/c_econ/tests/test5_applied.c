#include <stdlib.h>
#include "check.h"
#include "csv.h"
#include "ols.h"
#include "stats.h"
#include "topics.h"
#include "dist.h"
#include "expected.h"

/* Helper: fit y on the given columns (adds the intercept). */
static OLS *fit_cols(int n, const double *y, int ncols, const double *cols[]) {
    Matrix *X = design_matrix(n, ncols, cols);
    if (!X) return NULL;
    OLS *m = ols_fit(X, y);
    mat_free(X);
    return m;
}

int main(void) {
    printf("=== Stage 5: Chapter 6 and 7 applied to the data ===\n");
    Dataset *ds = dataset_load("data/sample30.csv");
    if (!ds) { printf("Could not open data/sample30.csv (run from the project root).\n"); return 1; }
    int n = ds->nrows;
    const double *educ = dataset_col(ds, "educ"), *exper = dataset_col(ds, "exper");
    const double *female = dataset_col(ds, "female"), *lwage = dataset_col(ds, "lwage");
    const double *highwage = dataset_col(ds, "highwage");
    double *tmp1 = malloc(n * sizeof(double)), *tmp2 = malloc(n * sizeof(double));
    double *tmp3 = malloc(n * sizeof(double));

    printf("-- quadratic in exper: lwage ~ educ + exper + exper^2\n");
    interact(exper, exper, n, tmp1);                           /* exper^2 */
    const double *qc[] = {educ, exper, tmp1};
    OLS *q = fit_cols(n, lwage, 3, qc);
    if (!q) check_true("quadratic model fitted", 0);
    else {
        double turn = quad_turning_point(q->beta[2], q->beta[3]);
        check_near("turning point of exper", turn, E3_TURN, 1e-7);
        check_near("marginal effect of exper at 10", quad_marginal_effect(q->beta[2], q->beta[3], 10.0), E3_ME10, 1e-8);
        check_true("players beyond the turning point", count_above(exper, n, turn) == (int)E3_ABOVE);
        const double *rc[] = {educ};
        OLS *r = fit_cols(n, lwage, 1, rc);                    /* restricted: no exper terms */
        if (r) {
            double F = f_stat_restrictions(r->ssr, q->ssr, 2, q->df);
            check_near("joint F: exper and exper^2 both zero", F, E3_JF, 1e-6);
            check_near("joint F p-value", f_pvalue(F, 2, q->df), E3_JFP, 1e-9);
        } else check_true("restricted model fitted", 0);
        ols_free(r);
    }
    ols_free(q);

    printf("-- interaction: lwage ~ educ + exper + educ*exper\n");
    interact(educ, exper, n, tmp1);
    const double *ic[] = {educ, exper, tmp1};
    OLS *im = fit_cols(n, lwage, 3, ic);
    if (!im) check_true("interaction model fitted", 0);
    else check_near("return to educ at exper=10 (b1 + 10*b3)",
                    interaction_effect(im->beta[1], im->beta[3], 10.0), E4_EFFECT10, 1e-8);
    ols_free(im);

    printf("-- recentering trick: educ*(exper - 10)\n");
    for (int i = 0; i < n; i++) tmp2[i] = educ[i] * (exper[i] - 10.0);
    const double *rcc[] = {educ, exper, tmp2};
    OLS *rm = fit_cols(n, lwage, 3, rcc);
    if (!rm) check_true("recentered model fitted", 0);
    else {
        check_near("coefficient on educ = theta_1", rm->beta[1], E4R_THETA, 1e-8);
        check_near("se(theta_1)", rm->se[1], E4R_SE, 1e-8);
        double c = t_critical(0.05, rm->df);
        check_near("95% CI low",  rm->beta[1] - c * rm->se[1], E4R_CI_LO, 1e-6);
        check_near("95% CI high", rm->beta[1] + c * rm->se[1], E4R_CI_HI, 1e-6);
    }
    ols_free(rm);

    printf("-- prediction at educ=12, exper=10\n");
    const double *pc[] = {educ, exper};
    OLS *pm = fit_cols(n, lwage, 2, pc);
    if (!pm) check_true("model fitted", 0);
    else {
        double x0[] = {1.0, 12.0, 10.0};
        Prediction pr = predict_at(pm, x0, 0.05);
        check_near("fit",                 pr.fit, EP_FIT, 1e-8);
        check_near("se of the average",   pr.se_mean, EP_SEMEAN, 1e-8);
        check_near("CI low (average)",    pr.ci_lo, EP_CI_LO, 1e-6);
        check_near("CI high (average)",   pr.ci_hi, EP_CI_HI, 1e-6);
        check_near("PI low (one person)", pr.pi_lo, EP_PI_LO, 1e-6);
        check_near("PI high (one person)", pr.pi_hi, EP_PI_HI, 1e-6);
        check_true("prediction interval is wider than the CI",
                   (pr.pi_hi - pr.pi_lo) > (pr.ci_hi - pr.ci_lo));
    }

    printf("-- standardized (beta) coefficients\n");
    double *zy = malloc(n * sizeof(double)), *ze = malloc(n * sizeof(double));
    double *zx = malloc(n * sizeof(double));
    standardize(lwage, n, zy); standardize(educ, n, ze); standardize(exper, n, zx);
    const double *zc[] = {ze, zx};
    OLS *zm = fit_cols(n, zy, 2, zc);
    if (!zm) check_true("standardized model fitted", 0);
    else {
        check_near("standardized beta, educ",  zm->beta[1], E5_ZB_EDUC, 1e-8);
        check_near("standardized beta, exper", zm->beta[2], E5_ZB_EXPER, 1e-8);
        check_near("intercept is ~0 when everything is standardized", zm->beta[0], 0.0, 1e-9);
    }
    ols_free(zm); free(zy); free(ze); free(zx);

    printf("-- Chow test: do women and men have the same equation?\n");
    double *ye[2], *e0[2], *x0s[2]; int cnt[2] = {0, 0};
    for (int g = 0; g < 2; g++) {
        ye[g] = malloc(n * sizeof(double)); e0[g] = malloc(n * sizeof(double));
        x0s[g] = malloc(n * sizeof(double));
    }
    for (int i = 0; i < n; i++) {
        int g = (int)female[i];
        ye[g][cnt[g]] = lwage[i]; e0[g][cnt[g]] = educ[i]; x0s[g][cnt[g]] = exper[i]; cnt[g]++;
    }
    double ssr_g[2] = {-1, -1};
    for (int g = 0; g < 2; g++) {
        const double *gc[] = {e0[g], x0s[g]};
        OLS *gm = fit_cols(cnt[g], ye[g], 2, gc);
        if (gm) ssr_g[g] = gm->ssr;
        ols_free(gm);
    }
    check_near("SSR, group 0", ssr_g[0], E6_SSR_G0, 1e-7);
    check_near("SSR, group 1", ssr_g[1], E6_SSR_G1, 1e-7);
    if (pm) check_near("Chow F", chow_f(pm->ssr, ssr_g[0], ssr_g[1], n, 3), E6_CHOW_F, 1e-6);
    for (int g = 0; g < 2; g++) { free(ye[g]); free(e0[g]); free(x0s[g]); }
    ols_free(pm);

    printf("-- linear probability model: highwage ~ educ + exper\n");
    const double *lc[] = {educ, exper};
    OLS *lm = fit_cols(n, highwage, 2, lc);
    if (!lm) check_true("LPM fitted", 0);
    else {
        check_near("intercept", lm->beta[0], E7_B0, 1e-8);
        check_near("educ",      lm->beta[1], E7_B1, 1e-8);
        check_near("exper",     lm->beta[2], E7_B2, 1e-8);
        check_true("fitted 'probabilities' outside [0,1]", count_outside_unit(lm->fitted, n) == (int)E7_OUTSIDE);
    }
    ols_free(lm);

    printf("-- dummy variable: female\n");
    make_dummy(female, n, 1.0, tmp3);
    check_true("dummy matches the female column", tmp3[0] == female[0] && tmp3[5] == female[5]);

    free(tmp1); free(tmp2); free(tmp3);
    dataset_free(ds);
    return check_summary();
}
