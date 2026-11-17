/* Sanity checks on the PROVIDED distribution code, so you can trust it. */
#include "check.h"
#include "dist.h"
#include "expected.h"

int main(void) {
    printf("=== Stage 0: provided t and F distributions ===\n");
    check_near("p-value, t=2.095, df=931",  t_pvalue_two_sided(2.095, 931), ED_P_T2095_DF931, 1e-9);
    check_near("p-value, t=1.0, df=10",     t_pvalue_two_sided(1.0, 10),    ED_P_T1_DF10, 1e-9);
    check_near("F p-value, F=0.518 (3,1685)", f_pvalue(0.518, 3, 1685),     ED_P_F0518, 1e-9);
    check_near("F p-value, F=5 (2,20)",     f_pvalue(5.0, 2, 20),           ED_P_F5_DF2_20, 1e-9);
    check_near("t critical 5%, df=10",      t_critical(0.05, 10),           ED_TCRIT_DF10, 1e-7);
    check_near("t critical 5%, df=1688",    t_critical(0.05, 1688),         ED_TCRIT_DF1688, 1e-7);
    check_true("tiny p-value is positive and tiny", t_pvalue_two_sided(-30.648, 1688) < 1e-15
               && t_pvalue_two_sided(-30.648, 1688) > 0.0);
    return check_summary();
}
