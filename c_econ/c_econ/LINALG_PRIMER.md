# The 10-minute linear algebra primer (only what OLS needs)

## 1. A matrix is a table
A `rows x cols` grid of numbers. In regression, X has one row per observation and one column per
variable (the first column is all 1s for the intercept); y is one column.

    X = [1 2]      y = [ 3]
        [1 4]          [ 5]
        [1 6]          [10]

## 2. Transpose: flip rows and columns
X' (read "X-transpose") has X's rows as its columns:

    X' = [1 1 1]
         [2 4 6]

Entry (i, j) of X' is entry (j, i) of X.

## 3. Multiplying: row-times-column
If A is `m x n` and B is `n x p`, then AB is `m x p` (the inner sizes must match, or the product
doesn't exist). Entry (i, j) of AB = (row i of A) dotted with (column j of B), meaning multiply
pairwise and add.

    X'X = [1 1 1] [1 2]   =  [ 3   12]      (1*1+1*1+1*1 = 3, 1*2+1*4+1*6 = 12, ...)
          [2 4 6] [1 4]      [12   56]
                  [1 6]

Look at what's inside: n, sum(x), sum(x), sum(x^2). And X'y = [sum(y); sum(xy)] = [18; 86].
Those sums are the building blocks of the OLS formulas.

## 4. The inverse: "dividing" for matrices
A^-1 is the matrix with A * A^-1 = I, where I (the identity) has 1s on the diagonal and 0s
elsewhere and acts like the number 1. For 2x2:

    [a b]^-1 = 1/(ad - bc) * [ d -b]
    [c d]                    [-c  a]

ad - bc is the determinant. If it's 0 there is **no inverse** (the matrix is "singular").
In regression this means perfectly collinear columns, and it is exactly what happens in the dummy
variable trap. For X'X above: determinant = 3*56 - 12*12 = 24, so
(X'X)^-1 = (1/24) [56 -12; -12 3].

## 5. The punchline
    beta_hat = (X'X)^-1 X'y            (here: [-1; 1.75], the intercept and slope you found by hand)
    Var(beta_hat) = sigma_hat^2 (X'X)^-1   -> standard errors are the square roots of its diagonal

## 6. Gauss-Jordan: how you compute an inverse
Write A next to the identity, [ A | I ], then use row operations (swap rows; multiply a row by a
number; add a multiple of one row to another) until the left side becomes I. The right side is then A^-1.
Example, A = [2 1; 1 3]:

    [2 1 | 1 0]   R1 / 2        ->  [1 0.5 |  0.5  0]
    [1 3 | 0 1]                     [1 3   |  0    1]
                  R2 - R1       ->  [1 0.5 |  0.5  0]
                                    [0 2.5 | -0.5  1]
                  R2 / 2.5      ->  [1 0.5 |  0.5  0  ]
                                    [0 1   | -0.2  0.4]
                  R1 - 0.5*R2   ->  [1 0   |  0.6 -0.2]
                                    [0 1   | -0.2  0.4]     <- this half is A^-1

Check: A * A^-1 = [2 1; 1 3] * [0.6 -0.2; -0.2 0.4] = [1 0; 0 1].
**Partial pivoting:** before dividing, swap up the row with the largest |value| in the current
column. It avoids dividing by tiny or zero numbers, and a pivot near 0 after that means the matrix is singular.

## Refreshers if you want more
3Blue1Brown's "Essence of linear algebra" series (the first four videos plus matrix multiplication)
is the quickest intuition builder. Gilbert Strang's MIT 18.06 lectures are the deeper dive.
