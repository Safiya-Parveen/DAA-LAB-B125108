#include <stdio.h>

int main()
{
    int n, k, i, j, min, count;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n], used[n];

    printf("Enter elements:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        used[i] = 0;
    }

    printf("Enter k: ");
    scanf("%d", &k);

    if (k < 1 || k > n)
    {
        printf("Invalid k\n");
        return 0;
    }

    /* Find kth smallest element */
    for (count = 0; count < k; count++)
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

    printf("%dth smallest element = %d\n", k, a[min]);

    return 0;
}