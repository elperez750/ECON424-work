# Econometrics from scratch, in C

You write the statistics. The tests tell you when you're right.
Every function you need to write is a `TODO` stub in `src/`. Every test already knows the correct
answers (computed independently in Python), so a red `FAIL` shows what your code returned next
to what it should have returned.

## Quick start
```
make test      # runs every stage; everything starts red
make t1        # run just Stage 1  (t0 .. t5)
```
Run from this folder (the tests read `data/sample30.csv`). If `-fsanitize` gives you trouble
(e.g. on Windows/MinGW), delete that flag in the Makefile.

## The data: `data/sample30.csv` (30 rows, made-up workers)
`educ` years of education, `exper` years of experience, `female` 0/1, `lwage` log hourly wage,
`highwage` 1 if lwage is above the median (used for the linear probability model).

## The stages
| Stage | You write | Needs matrices? | Chapter |
|---|---|---|---|
| 0 | nothing: `dist.c` is provided (t and F p-values, critical values) | no | 4-5 |
| 1 | `src/stats.c`: mean, variance, sd, cov, cor, and `simple_ols` (b0, b1, SST/SSE/SSR, R^2, sigma, SEs, t, p, CI) | **no** | 2-5 |
| 2 | `src/matrix.c`: matrix struct, transpose, multiply, inverse | it *is* the matrices | - |
| 3 | `src/ols.c`: `design_matrix`, `ols_fit` (any number of x's, plus adjusted R^2 and overall F) | yes | 3-5 |
| 4 | `src/topics.c`: quadratics, interaction effect, exact % change, adjusted R^2, F from SSRs, standardize, interact, dummies, Chow F, LPM check | **no** | 6-7 |
| 5 | `predict_at` in `src/topics.c`, then `make t5` checks the whole Chapter 6-7 workflow on the data | yes | 6-7 |

## Suggested order for Monday
Stages 1 and 4 need no linear algebra, and Stage 4 is exactly the new Chapter 6-7 material, so do
those first. Then Stages 2, 3, 5 when you have time. Before Stage 2, read `LINALG_PRIMER.md`
(about 10 minutes; it builds on the X'X example from your workbook).

## Things worth knowing
- **`k` is different here.** In `ols.h` and `topics.h`, `k` counts the intercept (columns of X).
  Wooldridge's `k` doesn't. Degrees of freedom are `n - k` in the code (his `n - k - 1`).
- **`lgamma`** (used inside `dist.c`, which you don't have to write) is ln(Gamma(x)). Gamma is the
  factorial extended to non-integers: Gamma(n) = (n-1)!. The t and F distributions are defined using
  it, and working with logs avoids overflow from enormous factorials. It lives in `<math.h>`; that
  is why the Makefile links with `-lm`.
- **Everything is `double`.** `int / int` truncates in C. Write `1.0 / n`, not `1 / n`.
- **Matrices are flat arrays.** Element (i, j) of a rows x cols matrix lives at `data[i * cols + j]`.
- **Memory:** every `malloc`/`calloc` needs a `free`. The sanitizer flags will tell you when you
  forgot, or when you read past the end of an array.
- `tools/make_expected.py` is how the expected answers were made. Change the data, rerun it, and
  every test updates.

## Beyond the tests (once everything is green)
A `main.c` that loads a CSV and prints something like R's `summary()` for a regression;
heteroskedasticity-robust standard errors (Chapter 8); a general `linearHypothesis` that
takes a list of coefficients to test.
