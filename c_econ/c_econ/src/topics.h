#ifndef TOPICS_H
#define TOPICS_H
#include "ols.h"

/* ---------- STAGE 4: new in Chapters 6 and 7 (formulas; no matrices needed) ---------- */

/* Chapter 6: quadratics, interactions, logs, fit */
double quad_turning_point(double b1, double b2);              /* -b1 / (2*b2) */
double quad_marginal_effect(double b1, double b2, double x);  /* b1 + 2*b2*x */
int    count_above(const double *x, int n, double cutoff);    /* how many x[i] > cutoff */
double interaction_effect(double b1, double b3, double z);    /* b1 + b3*z */
double pct_change_exact(double b, double dx);                 /* 100*(exp(b*dx) - 1) */
double adjusted_r2(double r2, int n, int k);                  /* k includes intercept */
double f_stat_restrictions(double ssr_r, double ssr_ur, int q, int df_ur);
void   standardize(const double *x, int n, double *out);      /* z-scores: (x-mean)/sd */
void   interact(const double *a, const double *b, int n, double *out);   /* a[i]*b[i] */

/* Chapter 7: dummies, Chow test, linear probability model */
void   make_dummy(const double *cat, int n, double value, double *out);  /* 1 if cat[i]==value */
double chow_f(double ssr_pooled, double ssr1, double ssr2, int n, int k);/* k includes intercept */
int    count_outside_unit(const double *fitted, int n);       /* fitted < 0 or > 1 */

/* ---------- STAGE 5: prediction (needs a fitted OLS model) ---------- */
typedef struct {
    double fit;                 /* predicted value at x0 */
    double se_mean;             /* standard error of the fitted average */
    double ci_lo, ci_hi;        /* interval for the AVERAGE y at x0 */
    double pi_lo, pi_hi;        /* interval for ONE new y at x0 */
} Prediction;

/* x0 has length m->k and starts with 1 (the intercept). alpha = 0.05 for 95%. */
Prediction predict_at(const OLS *m, const double *x0, double alpha);

#endif
