#ifndef STATS_H
#define STATS_H

/* ---------- STAGE 1: the essentials (no matrices needed) ---------- */

double mean(const double *x, int n);
double variance(const double *x, int n);                 /* SAMPLE variance: divide by n-1 */
double std_dev(const double *x, int n);
double covariance(const double *x, const double *y, int n);   /* sample: divide by n-1 */
double correlation(const double *x, const double *y, int n);

/* Everything you get from regressing y on ONE x (plus an intercept). */
typedef struct {
    int    n;
    double b0, b1;                 /* intercept, slope */
    double sst, sse, ssr;          /* total, explained, residual sums of squares */
    double r2;
    double sigma_hat;              /* standard error of the regression */
    double se_b0, se_b1;           /* coefficient standard errors */
    double t_b0, t_b1;             /* t statistics for H0: beta = 0 */
    double p_b0, p_b1;             /* two-sided p-values */
    double ci_b1_lo, ci_b1_hi;     /* 95% confidence interval for the slope */
} SimpleOLS;

SimpleOLS simple_ols(const double *x, const double *y, int n);

#endif
