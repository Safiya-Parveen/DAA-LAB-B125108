#include <stdio.h>

int main()
{
    int n;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    int possible[100];

    // Initially target can be anywhere
    for (int i = 0; i < n; i++)
        possible[i] = 1;

    int shots[200];
    int count = 0;

    // Special case
    if (n == 2)
    {
        shots[count++] = 0;
        shots[count++] = 0;
    }
    else
    {
        // Left to right
        for (int i = 1; i < n - 1; i++)
            shots[count++] = i;

        // Right to left
        for (int i = n - 2; i >= 1; i--)
            shots[count++] = i;
    }

    for (int s = 0; s < count; s++)
    {
        int shot = shots[s];

        // Shooter shoots here
        possible[shot] = 0;

        // If no possible position remains
        int any = 0;

        for (int i = 0; i < n; i++)
        {
            if (possible[i])
                any = 1;
        }

        if (!any)
        {
            printf("Target hit!\n");
            return 0;
        }

        // Target must move to adjacent position
        int next[100] = {0};

        for (int i = 0; i < n; i++)
        {
            if (possible[i])
            {
                if (i > 0)
                    next[i - 1] = 1;

                if (i < n - 1)
                    next[i + 1] = 1;
            }
        }

        for (int i = 0; i < n; i++)
            possible[i] = next[i];
    }

    printf("Target was not guaranteed to be hit.\n");

    return 0;
}