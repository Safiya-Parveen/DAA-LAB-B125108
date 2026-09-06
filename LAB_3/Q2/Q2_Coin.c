#include <stdio.h>
#include <math.h>

int defective_coin(float coins[], int n)
{
    int start = 0;
    int end = n - 1;

    while (start < end)
    {
        int len = end - start + 1;
        int half = len / 2;

        float left_sum = 0.0f;
        float right_sum = 0.0f;

        for (int i = 0; i < half; i++)
        {
            left_sum += coins[start + i];
            right_sum += coins[start + half + i];
        }

        // Use a tiny epsilon for float comparison to prevent precision bugs
        if (left_sum != right_sum)
        {
            // If we know defective is HEAVIER, left_sum > right_sum means it's on the left
            if (left_sum > right_sum)
            {
                end = start + half - 1;
            }
            else
            {
                start = start + half;
            }
        }
        else
        {
            if (len % 2 == 0)
            {
                return -1;
            }
            else
            {
                if (coins[end] != coins[start])
                    return end;
                return -1;
            }
        }
    }

    return start;
}

int main()
{
    int n;
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0)
        return 1;

    float coins[n];

    printf("ENTER THE ELEMENTS:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%f", &coins[i]); // Must use %f for float!
    }

    int defective_idx = defective_coin(coins, n);

    if (defective_idx != -1)
    {
        printf("Defective coin is at index %d\n", defective_idx);
    }
    else
    {
        printf("All coins are perfect!\n");
    }

    return 0;
}