#include <stdio.h>

int dp[100];
int split[100];

int power2(int n)
{
    int result = 1;

    for (int i = 0; i < n; i++)
        result = result * 2;

    return result;
}

void threePeg(int n, char from, char to, char aux)
{
    if (n == 0)
        return;

    threePeg(n - 1, from, aux, to);

    printf("Move disk from %c to %c\n", from, to);

    threePeg(n - 1, aux, to, from);
}

void fourPeg(int n, char from, char to, char aux1, char aux2)
{
    if (n == 0)
        return;

    if (n == 1)
    {
        printf("Move disk from %c to %c\n", from, to);
        return;
    }

    int k = split[n];

    fourPeg(k, from, aux1, to, aux2);

    threePeg(n - k, from, to, aux2);

    fourPeg(k, aux1, to, from, aux2);
}

int main()
{
    int n = 8;

    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = 999999;

        for (int k = 1; k < i; k++)
        {
            int moves = 2 * dp[k] + power2(i - k) - 1;

            if (moves < dp[i])
            {
                dp[i] = moves;
                split[i] = k;
            }
        }
    }

    printf("Minimum moves = %d\n", dp[n]);

    printf("\nMoves:\n");

    fourPeg(n, 'A', 'D', 'B', 'C');

    return 0;
}