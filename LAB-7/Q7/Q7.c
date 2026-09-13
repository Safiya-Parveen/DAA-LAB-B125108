#include <stdio.h>

#define INF 999999

int dp[20][20];
int split[20][20];

void printOrder(int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }

    printf("(");

    printOrder(i, split[i][j]);

    printf(" x ");

    printOrder(split[i][j] + 1, j);

    printf(")");
}

int main()
{
    int n;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    int p[20];

    printf("Enter dimensions:\n");

    for (int i = 0; i <= n; i++)
        scanf("%d", &p[i]);

    // Cost of multiplying one matrix = 0
    for (int i = 1; i <= n; i++)
        dp[i][i] = 0;

    // Length of chain
    for (int length = 2; length <= n; length++)
    {
        for (int i = 1; i <= n - length + 1; i++)
        {
            int j = i + length - 1;

            dp[i][j] = INF;

            for (int k = i; k < j; k++)
            {
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];

                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum scalar multiplications = %d\n",
           dp[1][n]);

    printf("Best order = ");
    printOrder(1, n);

    printf("\n");

    return 0;
}