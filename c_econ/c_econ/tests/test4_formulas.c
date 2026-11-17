#include "check.h"
#include "topics.h"
#include "stats.h"
#include "expected.h"

int main(void) {
    printf("=== Stage 4: Chapter 6 and 7 formulas (no matrices needed) ===\n");

    printf("-- quadratics\n");
    check_near("turning point, b1=2, b2=-0.1  -> 10", quad_turning_point(2.0, -0.1), 10.0, 1e-9);
    check_near("turning point, b1=0.04, b2=-0.0006", quad_turning_point(0.04, -0.0006), 0.04 / 0.0012, 1e-9);
    check_near("marginal effect at x=2  -> 1.6", quad_marginal_effect(2.0, -0.1, 2.0), 1.6, 1e-9);
    check_near("marginal effect at x=8  -> 0.4", quad_marginal_effect(2.0, -0.1, 8.0), 0.4, 1e-9);
    double ex[] = {1, 5, 9, 12};
    check_true("count_above({1,5,9,12}, 5) = 2 (strictly greater)", count_above(ex, 4, 5.0) == 2);

    printf("-- interactions and logs\n");
    check_near("interaction effect 0.05 + 0.002*10", interaction_effect(0.05, 0.002, 10.0), 0.07, 1e-12);
    check_near("exact % change, b=0.09", pct_change_exact(0.09, 1.0), EF_PCT_009, 1e-9);
    check_near("exact % change, b=0.40 (approx would say 40)", pct_change_exact(0.4, 1.0), EF_PCT_04, 1e-9);
    check_near("exact % change, b=0.05, dx=10", pct_change_exact(0.05, 10.0), 100.0 * (exp(0.5) - 1.0), 1e-9);

    printf("-- fit and tests\n");
    check_near("adjusted R^2 (0.6724, n=88, k=4)", adjusted_r2(0.6724, 88, 4), EF_ADJR2, 1e-9);
    check_near("F from SSRs (395269, 394904, q=3, df=1685)",
               f_stat_restrictions(395269.0, 394904.0, 3, 1685), EF_F_RESTR, 1e-9);

    printf("-- building variables\n");
    double a[] = {1, 2, 3}, b[] = {4, 5, 6}, out[3] = {-9, -9, -9};
    interact(a, b, 3, out);
    check_true("interact({1,2,3},{4,5,6}) = {4,10,18}", out[0] == 4 && out[1] == 10 && out[2] == 18);
    standardize(a, 3, out);
    check_true("standardize({1,2,3}) = {-1,0,1}",
               fabs(out[0] + 1) < 1e-9 && fabs(out[1]) < 1e-9 && fabs(out[2] - 1) < 1e-9);
    double cat[] = {0, 1, 1, 0}, d[4] = {-9, -9, -9, -9};
    make_dummy(cat, 4, 1.0, d);
    check_true("make_dummy({0,1,1,0}, 1) = {0,1,1,0}", d[0] == 0 && d[1] == 1 && d[2] == 1 && d[3] == 0);
    make_dummy(cat, 4, 0.0, d);
    check_true("make_dummy({0,1,1,0}, 0) = {1,0,0,1}", d[0] == 1 && d[1] == 0 && d[2] == 0 && d[3] == 1);

    printf("-- Chapter 7\n");
    check_near("Chow F (50, 20, 25, n=40, k=3)", chow_f(50.0, 20.0, 25.0, 40, 3), EF_CHOW, 1e-9);
    double fv[] = {-0.1, 0.5, 1.0, 1.2};
    check_true("count_outside_unit({-0.1,0.5,1.0,1.2}) = 2", count_outside_unit(fv, 4) == 2);

    return check_summary();
}
