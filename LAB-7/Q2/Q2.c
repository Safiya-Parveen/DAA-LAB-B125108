#include <stdio.h>

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int main()
{
    int E, F;

    printf("Enter number of eggs: ");
    scanf("%d", &E);

    printf("Enter number of floors: ");
    scanf("%d", &F);

    int dp[E + 1][F + 1];

    // With 0 or 1 floor
    for (int e = 1; e <= E; e++)
    {
        dp[e][0] = 0;
        dp[e][1] = 1;
    }

    // With only 1 egg
    for (int f = 0; f <= F; f++)
    {
        dp[1][f] = f;
    }

    // DP
    for (int e = 2; e <= E; e++)
    {
        for (int f = 2; f <= F; f++)
        {
            dp[e][f] = 999999;

            for (int x = 1; x <= f; x++)
            {
                int breaks = dp[e - 1][x - 1];
                int notBreak = dp[e][f - x];

                int worst = max(breaks, notBreak);

                if (worst + 1 < dp[e][f])
                    dp[e][f] = worst + 1;
            }
        }
    }

    printf("Minimum drops = %d\n", dp[E][F]);

    return 0;
}