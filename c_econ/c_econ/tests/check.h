#ifndef CHECK_H
#define CHECK_H
#include <stdio.h>
#include <math.h>

static int g_pass = 0, g_fail = 0;

static inline void check_near(const char *name, double got, double want, double tol) {
    if (fabs(got - want) <= tol) { printf("  PASS  %s\n", name); g_pass++; }
    else { printf("  FAIL  %s\n          got %.10g, expected %.10g\n", name, got, want); g_fail++; }
}

static inline void check_true(const char *name, int cond) {
    if (cond) { printf("  PASS  %s\n", name); g_pass++; }
    else { printf("  FAIL  %s\n", name); g_fail++; }
}

static inline int check_summary(void) {
    printf("\n  %d passed, %d failed\n", g_pass, g_fail);
    return g_fail ? 1 : 0;
}
#endif
