#include <math.h>
#include "dist.h"

/* Regularized incomplete beta function I_x(a,b), via a continued fraction.
 * Both the t and F p-values are special cases of it:
 *   two-sided t p-value : I_x(df/2, 1/2),     x = df / (df + t^2)
 *   F upper-tail p-value: I_x(df2/2, df1/2),  x = df2 / (df2 + df1 * f)
 * lgamma(z) = ln(Gamma(z)); Gamma generalizes the factorial (Gamma(n) = (n-1)!).
 * Working with logs avoids overflow from huge factorials. */

#define MAXIT 500
#define EPS   1.0e-15
#define FPMIN 1.0e-300

static double betacf(double a, double b, double x) {
    double qab = a + b, qap = a + 1.0, qam = a - 1.0;
    double c = 1.0, d = 1.0 - qab * x / qap;
    if (fabs(d) < FPMIN) d = FPMIN;
    d = 1.0 / d;
    double h = d;
    for (int m = 1; m <= MAXIT; m++) {
        int m2 = 2 * m;
        double aa = m * (b - m) * x / ((qam + m2) * (a + m2));
        d = 1.0 + aa * d; if (fabs(d) < FPMIN) d = FPMIN;
        c = 1.0 + aa / c; if (fabs(c) < FPMIN) c = FPMIN;
        d = 1.0 / d; h *= d * c;
        aa = -(a + m) * (qab + m) * x / ((a + m2) * (qap + m2));
        d = 1.0 + aa * d; if (fabs(d) < FPMIN) d = FPMIN;
        c = 1.0 + aa / c; if (fabs(c) < FPMIN) c = FPMIN;
        d = 1.0 / d;
        double del = d * c;
        h *= del;
        if (fabs(del - 1.0) < EPS) break;
    }
    return h;
}

static double reg_inc_beta(double x, double a, double b) {
    if (x <= 0.0) return 0.0;
    if (x >= 1.0) return 1.0;
    double bt = exp(lgamma(a + b) - lgamma(a) - lgamma(b) + a * log(x) + b * log1p(-x));
    if (x < (a + 1.0) / (a + b + 2.0)) return bt * betacf(a, b, x) / a;
    return 1.0 - bt * betacf(b, a, 1.0 - x) / b;
}

double t_pvalue_two_sided(double t, double df) {
    return reg_inc_beta(df / (df + t * t), df / 2.0, 0.5);
}

double t_critical(double alpha, double df) {
    double lo = 0.0, hi = 1000.0;
    for (int i = 0; i < 200; i++) {                 /* bisection */
        double mid = 0.5 * (lo + hi);
        if (t_pvalue_two_sided(mid, df) > alpha) lo = mid; else hi = mid;
    }
    return 0.5 * (lo + hi);
}

double f_pvalue(double f, double df1, double df2) {
    if (f <= 0.0) return 1.0;
    return reg_inc_beta(df2 / (df2 + df1 * f), df2 / 2.0, df1 / 2.0);
}
