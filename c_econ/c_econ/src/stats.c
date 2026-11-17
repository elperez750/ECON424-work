#include <math.h>
#include <string.h>
#include "stats.h"
#include "dist.h"      /* t_pvalue_two_sided(), t_critical() are PROVIDED for you */

/* TODO: replace each "return NAN" with a real implementation. */

double mean(const double *x, int n) {
    /* sum of x_i divided by n */
    return NAN;
}

double variance(const double *x, int n) {
    /* sum of (x_i - xbar)^2, divided by (n - 1) */
    return NAN;
}

double std_dev(const double *x, int n) {
    /* square root of the variance */
    return NAN;
}

double covariance(const double *x, const double *y, int n) {
    /* sum of (x_i - xbar)(y_i - ybar), divided by (n - 1) */
    return NAN;
}

double correlation(const double *x, const double *y, int n) {
    /* cov(x,y) / (sd(x) * sd(y)) */
    return NAN;
}

SimpleOLS simple_ols(const double *x, const double *y, int n) {
    SimpleOLS r;
    memset(&r, 0, sizeof r);       /* all fields start at 0 */
    r.n = n;

    /* TODO, in this order (each step uses the one before):
     *  1. b1 = sum (x-xbar)(y-ybar) / sum (x-xbar)^2        b0 = ybar - b1*xbar
     *  2. SST = sum (y-ybar)^2   SSR = sum (y - b0 - b1*x)^2   SSE = SST - SSR
     *  3. r2 = 1 - SSR/SST
     *  4. sigma_hat = sqrt( SSR / (n - 2) )          (n-2: two estimated parameters)
     *  5. se_b1 = sigma_hat / sqrt( sum (x-xbar)^2 )
     *     se_b0 = sigma_hat * sqrt( 1/n + xbar^2 / sum (x-xbar)^2 )
     *  6. t = estimate / se        p = t_pvalue_two_sided(t, n - 2)
     *  7. ci = b1 -/+ t_critical(0.05, n - 2) * se_b1
     */
    return r;
}
