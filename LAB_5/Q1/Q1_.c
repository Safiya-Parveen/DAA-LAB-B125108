#include <stdio.h>

int main()
{
    int n, i, j, min, count;
    int first, second;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n], used[n];

    printf("Enter elements:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        used[i] = 0;
    }

    if (n % 2 == 1)
    {
        /* Odd number of elements */
        for (count = 0; count <= n / 2; count++)
        {
            min = -1;

            for (i = 0; i < n; i++)
            {
                if (used[i] == 0)
                {
                    if (min == -1 || a[i] < a[min])
                        min = i;
                }
            }

            used[min] = 1;
        }

        printf("Median = %d\n", a[min]);
    }
    else
    {
        /* Even number of elements */

        /* Find n/2-th smallest */
        for (count = 0; count < n / 2; count++)
        {
            min = -1;

            for (i = 0; i < n; i++)
            {
                if (used[i] == 0)
                {
                    if (min == -1 || a[i] < a[min])
                        min = i;
                }
            }

            used[min] = 1;
        }

        first = a[min];

        /* Find (n/2 + 1)-th smallest */
        min = -1;

        for (i = 0; i < n; i++)
        {
            if (used[i] == 0)
            {
                if (min == -1 || a[i] < a[min])
                    min = i;
            }
        }

        second = a[min];

        printf("Median = %.2f\n", (first + second) / 2.0);
    }

    return 0;
}