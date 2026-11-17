#ifndef DIST_H
#define DIST_H
/* PROVIDED: the t and F distributions. You CALL these; you don't need to write them.
 * (Read dist.c later if you're curious how p-values are computed.) */

/* Two-sided p-value for a t statistic:  P(|T| > |t|)  with df degrees of freedom. */
double t_pvalue_two_sided(double t, double df);

/* Critical value c such that P(|T| > c) = alpha  (e.g. alpha = 0.05, large df -> ~1.96). */
double t_critical(double alpha, double df);

/* Upper-tail p-value for an F statistic: P(F > f) with (df1, df2) degrees of freedom. */
double f_pvalue(double f, double df1, double df2);

#endif
