#include <stdio.h>

int main()
{
    int n;
    int total;
    int moves;

    printf("Enter number of rows: ");
    scanf("%d", &n);

    // Total number of coins
    total = n * (n + 1) / 2;

    // Minimum number of coins to move
    moves = total / 3;

    printf("\nOriginal Triangle:\n");

    // Print original triangle
    for (int i = 1; i <= n; i++)
    {
        // Spaces
        for (int j = 1; j <= n - i; j++)
            printf(" ");

        // Coins
        for (int j = 1; j <= i; j++)
            printf("O ");

        printf("\n");
    }

    printf("\nMinimum coins to move = %d\n", moves);

    printf("\nInverted Triangle:\n");

    // Print inverted triangle
    for (int i = n; i >= 1; i--)
    {
        // Spaces
        for (int j = 1; j <= n - i; j++)
            printf(" ");

        // Coins
        for (int j = 1; j <= i; j++)
            printf("O ");

        printf("\n");
    }

    return 0;
}