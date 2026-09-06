#include <stdio.h>
#include <stdlib.h>

// Simple comparison function for standard qsort
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n, T;

    printf("Enter number of elements in set: ");
    scanf("%d", &n);

    if (n < 3)
    {
        printf("Need at least 3 elements for 3-Sum.\n");
        return 0;
    }

    int *S = (int *)malloc(n * sizeof(int));
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &S[i]);
    }

    printf("Enter Target Sum (T): ");
    scanf("%d", &T);

    // Step 1: Sort the array in O(n log n)
    qsort(S, n, sizeof(int), compare);

    int found = 0;

    // Step 2: Fix the first element S[i] using a simple loop
    for (int i = 0; i < n - 2; i++)
    {

        // Step 3: Two-pointer technique for the remaining 2 elements
        int left = i + 1;
        int right = n - 1;

        while (left < right)
        {
            int current_sum = S[i] + S[left] + S[right];

            if (current_sum == T)
            {
                printf("\nFound combination: %d + %d + %d = %d\n", S[i], S[left], S[right], T);
                found = 1;
                break; // Found a solution
            }
            else if (current_sum < T)
            {
                left++; // Sum is too small -> move left pointer rightwards
            }
            else
            {
                right--; // Sum is too big -> move right pointer leftwards
            }
        }

        if (found)
            break;
    }

    if (!found)
    {
        printf("\nNo 3 elements add up to %d\n", T);
    }

    free(S);
    return 0;
}