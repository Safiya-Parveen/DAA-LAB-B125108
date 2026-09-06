/*
Increasing Order of Growth (Asymptotic Analysis)

For sufficiently large values of n, the given functions grow
in the following order:

1.  1/n               -> Inverse Function (Approaches 0)
2.  log2(n)           -> Logarithmic
3.  12*sqrt(n)        -> Square Root
4.  50*sqrt(n)        -> Square Root (Different Constant)
5.  n^0.51            -> Fractional Polynomial
6.  2^32 * n          -> Linear (Large Constant Factor)
7.  n*log2(n)         -> Linearithmic
8.  100n^2 + 6n       -> Quadratic
9.  n^2 - 324         -> Quadratic
10. 2n^3              -> Cubic
11. n^(log2(n))       -> Quasi-Polynomial
12. 3^n               -> Exponential

Notes:
- Constant factors do not affect asymptotic growth.
- Lower-order terms become insignificant for large n.
- Functions having the same dominant term belong to the same
  asymptotic complexity class.
*/

#include <stdio.h>
#include <math.h>

#define TWO_POW_32 4294967296.0

int main(void)
{
    printf("\n========== ORDER OF GROWTH ANALYSIS ==========\n\n");

    /* ---------------- Small Growth ---------------- */

    printf("Small Growth Functions: \n");
    printf("-----------------------------------------------------------------------------\n");
    printf("%5s %10s %10s %14s %14s %12s\n",
           "n", "1/n", "log2(n)", "12*sqrt(n)", "50*sqrt(n)", "n^0.51");
    printf("-----------------------------------------------------------------------------\n");

    for (int n = 10; n <= 50; n += 10)
    {
        printf("%5d %10.4f %10.2f %14.2f %14.2f %12.2f\n",
               n,
               1.0 / n,
               log2(n),
               12.0 * sqrt(n),
               50.0 * sqrt(n),
               pow(n, 0.51));
    }

    printf("\n");

    /* ---------------- Medium Growth ---------------- */

    printf("Medium Growth Functions: \n");
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("%5s %18s %14s %16s %14s %14s\n",
           "n", "(2^32)*n", "nlog2(n)", "100n^2+6n", "n^2-324", "2n^3");
    printf("-----------------------------------------------------------------------------------------------\n");

    for (int n = 10; n <= 50; n += 10)
    {
        printf("%5d %18.0f %14.2f %16.0f %14.0f %14.0f\n",
               n,
               TWO_POW_32 * n,
               n * log2(n),
               100.0 * n * n + 6.0 * n,
               (double)(n * n - 324),
               2.0 * n * n * n);
    }

    printf("\n");

    /* ---------------- Fast Growth ---------------- */

    printf("Fast Growth Functions: \n");
    printf("--------------------------------------------------------------\n");
    printf("%5s %20s %20s\n",
           "n", "n^(log2(n))", "3^n");
    printf("--------------------------------------------------------------\n");

    for (int n = 10; n <= 50; n += 10)
    {
        printf("%5d %20.2e %20.2e\n",
               n,
               pow(n, log2(n)),
               pow(3.0, n));
    }

    return 0;
}