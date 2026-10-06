#include <stdio.h>

#define MAX 50

long long dp[MAX][MAX];
int root[MAX][MAX];
long long prefix[MAX];

long long sum(int i, int j)
{
    return prefix[j + 1] - prefix[i];
}

void printTree(int i, int j)
{
    if (i > j)
        return;

    int k = root[i][j];

    printf("w%d", k + 1);

    if (i != j)
    {
        printf("(");

        printTree(i, k - 1);

        printf(",");

        printTree(k + 1, j);

        printf(")");
    }
}

int main()
{
    int n;

    printf("Enter number of weights: ");
    scanf("%d", &n);

    long long w[n];

    printf("Enter weights in sorted/alphabetic order:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &w[i]);

        prefix[i + 1] = prefix[i] + w[i];
    }

    // One element has cost 0
    for (int i = 0; i < n; i++)
    {
        dp[i][i] = 0;
        root[i][i] = i;
    }

    // Length of interval
    for (int length = 2; length <= n; length++)
    {
        for (int i = 0; i + length - 1 < n; i++)
        {
            int j = i + length - 1;

            dp[i][j] = 1000000000000000000LL;

            // Try every element as root
            for (int k = i; k <= j; k++)
            {
                long long left = 0;
                long long right = 0;

                if (k > i)
                    left = dp[i][k - 1];

                if (k < j)
                    right = dp[k + 1][j];

                long long cost =
                    left + right + sum(i, j);

                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                    root[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum weighted path length = %lld\n",
           dp[0][n - 1]);

    printf("Optimal alphabetic tree = ");

    printTree(0, n - 1);

    printf("\n");

    return 0;
}