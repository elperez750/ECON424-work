#include "check.h"
#include "csv.h"
#include "stats.h"
#include "expected.h"

int main(void) {
    printf("=== Stage 1: essentials ===\n");
    Dataset *ds = dataset_load("data/sample30.csv");
    if (!ds) { printf("Could not open data/sample30.csv (run from the project root).\n"); return 1; }
    const double *educ = dataset_col(ds, "educ"), *lwage = dataset_col(ds, "lwage");
    int n = ds->nrows;

    printf("-- descriptive statistics (30 rows)\n");
    check_near("mean(educ)",        mean(educ, n),               E_MEAN_EDUC, 1e-9);
    check_near("variance(educ)",    variance(educ, n),           E_VAR_EDUC, 1e-9);
    check_near("std_dev(educ)",     std_dev(educ, n),            E_SD_EDUC, 1e-9);
    check_near("cov(educ, lwage)",  covariance(educ, lwage, n),  E_COV_EDUC_LWAGE, 1e-9);
    check_near("cor(educ, lwage)",  correlation(educ, lwage, n), E_COR_EDUC_LWAGE, 1e-9);

    printf("-- tiny example: x=(2,4,6), y=(3,5,10)   [Section H of the workbook]\n");
    double tx[] = {2, 4, 6}, ty[] = {3, 5, 10};
    SimpleOLS s = simple_ols(tx, ty, 3);
    check_near("intercept = -1",       s.b0, -1.0, 1e-9);
    check_near("slope = 1.75",         s.b1, 1.75, 1e-9);
    check_near("SST = 26",             s.sst, 26.0, 1e-9);
    check_near("SSR = 1.5",            s.ssr, 1.5, 1e-9);
    check_near("SSE = 24.5",           s.sse, 24.5, 1e-9);
    check_near("R^2 = 24.5/26",        s.r2, 24.5 / 26.0, 1e-9);
    check_near("sigma_hat = sqrt(1.5)", s.sigma_hat, 1.224744871391589, 1e-9);
    check_near("se(slope)",            s.se_b1, 0.4330127018922193, 1e-9);

    printf("-- lwage on educ, 30 rows\n");
    SimpleOLS r = simple_ols(educ, lwage, n);
    check_near("b0",        r.b0, E1_B0, 1e-8);
    check_near("b1",        r.b1, E1_B1, 1e-8);
    check_near("SST",       r.sst, E1_SST, 1e-8);
    check_near("SSE",       r.sse, E1_SSE, 1e-8);
    check_near("SSR",       r.ssr, E1_SSR, 1e-8);
    check_near("R^2",       r.r2, E1_R2, 1e-9);
    check_near("sigma_hat", r.sigma_hat, E1_SIGMA, 1e-9);
    check_near("se(b0)",    r.se_b0, E1_SE0, 1e-9);
    check_near("se(b1)",    r.se_b1, E1_SE1, 1e-9);
    check_near("t(b0)",     r.t_b0, E1_T0, 1e-7);
    check_near("t(b1)",     r.t_b1, E1_T1, 1e-7);
    check_near("p(b0)",     r.p_b0, E1_P0, 1e-9);
    check_near("p(b1)",     r.p_b1, E1_P1, 1e-9);
    check_near("95% CI low (slope)",  r.ci_b1_lo, E1_CI1_LO, 1e-7);
    check_near("95% CI high (slope)", r.ci_b1_hi, E1_CI1_HI, 1e-7);

    dataset_free(ds);
    return check_summary();
}
