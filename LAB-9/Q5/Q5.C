#include <stdio.h>

int main()
{
    int n;

    printf("Enter number of children: ");
    scanf("%d", &n);

    int rating[n];
    int candy[n];

    printf("Enter ratings:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &rating[i]);
        candy[i] = 1;
    }

    // Left to right
    for (int i = 1; i < n; i++)
    {
        if (rating[i] > rating[i - 1])
        {
            candy[i] = candy[i - 1] + 1;
        }
    }

    // Right to left
    for (int i = n - 2; i >= 0; i--)
    {
        if (rating[i] > rating[i + 1])
        {
            if (candy[i] < candy[i + 1] + 1)
                candy[i] = candy[i + 1] + 1;
        }
    }

    int total = 0;

    printf("Candies: ");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", candy[i]);
        total += candy[i];
    }

    printf("\nMinimum candies = %d\n", total);

    return 0;
}