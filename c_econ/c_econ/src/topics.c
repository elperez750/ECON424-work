#include <math.h>
#include <string.h>
#include "topics.h"
#include "stats.h"
#include "dist.h"

/* TODO: replace each stub with a real implementation. Formulas are in the comments. */

double quad_turning_point(double b1, double b2) {
    /* y = b0 + b1*x + b2*x^2  has slope zero at x* = -b1 / (2*b2) */
    return NAN;
}

double quad_marginal_effect(double b1, double b2, double x) {
    /* derivative of b1*x + b2*x^2 with respect to x */
    return NAN;
}

int count_above(const double *x, int n, double cutoff) {
    /* how many observations are strictly greater than cutoff
     * (your sum(nbasal$exper > turn) line in R) */
    return -1;
}

double interaction_effect(double b1, double b3, double z) {
    /* effect of x on y when the other variable equals z, in the model with b3*(x*z) */
    return NAN;
}

double pct_change_exact(double b, double dx) {
    /* log-level model: exact percent change in y when x rises by dx */
    return NAN;
}

double adjusted_r2(double r2, int n, int k) {
    /* 1 - (1 - r2) * (n - 1) / (n - k)      (k counts the intercept) */
    return NAN;
}

double f_stat_restrictions(double ssr_r, double ssr_ur, int q, int df_ur) {
    /* F = ((ssr_r - ssr_ur) / q) / (ssr_ur / df_ur)
     * q = number of restrictions, df_ur = n - k of the UNRESTRICTED model */
    return NAN;
}

void standardize(const double *x, int n, double *out) {
    /* out[i] = (x[i] - mean(x)) / std_dev(x)   (use your stats.c functions) */
}

void interact(const double *a, const double *b, int n, double *out) {
    /* out[i] = a[i] * b[i] */
}

void make_dummy(const double *cat, int n, double value, double *out) {
    /* out[i] = 1.0 if cat[i] == value, else 0.0 */
}

double chow_f(double ssr_pooled, double ssr1, double ssr2, int n, int k) {
    /* F = ((ssr_pooled - (ssr1 + ssr2)) / k) / ((ssr1 + ssr2) / (n - 2*k))
     * n = total observations, k = parameters per group INCLUDING the intercept */
    return NAN;
}

int count_outside_unit(const double *fitted, int n) {
    /* how many fitted values are below 0 or above 1 (linear probability model problem) */
    return -1;
}

Prediction predict_at(const OLS *m, const double *x0, double alpha) {
    Prediction p;
    memset(&p, 0, sizeof p);
    /* TODO:
     *  fit     = sum_j x0[j] * beta[j]
     *  v       = x0' * xtx_inv * x0          (a single number: do it with loops)
     *  se_mean = sigma_hat * sqrt(v)
     *  c       = t_critical(alpha, df)
     *  ci      = fit -/+ c * se_mean
     *  se_pred = sqrt( se_mean^2 + sigma_hat^2 )     <- the extra sigma_hat^2 is the
     *            unexplained variation of ONE new observation
     *  pi      = fit -/+ c * se_pred
     */
    return p;
}
