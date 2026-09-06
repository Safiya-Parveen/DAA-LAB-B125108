#include <stdio.h>
#include <stdlib.h>

// Standard integer comparator for qsort
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n;

    printf("Enter total number of intervals (n): ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid input size.\n");
        return 1;
    }

    int *L = (int *)malloc(n * sizeof(int)); // Left endpoints
    int *R = (int *)malloc(n * sizeof(int)); // Right endpoints

    printf("Enter intervals as (l, r) pairs (e.g., '10 40'):\n");
    for (int k = 0; k < n; k++)
    {
        printf("Interval %d: ", k + 1);
        scanf("%d %d", &L[k], &R[k]);
    }

    // Step 1: Sort left and right endpoints independently in O(n log n)
    qsort(L, n, sizeof(int), compare);
    qsort(R, n, sizeof(int), compare);

    // Step 2: Two-pointer sweep in O(n)
    int i = 0, j = 0;
    int current_intervals = 0;
    int max_intervals = 0;
    int best_point = -1;

    while (i < n && j < n)
    {
        // L[i] <= R[j] handles inclusive boundaries (e.g., L=50, R=50 counts both)
        if (L[i] <= R[j])
        {
            current_intervals++;

            if (current_intervals > max_intervals)
            {
                max_intervals = current_intervals;
                best_point = L[i]; // The point where overlap increases
            }
            i++; // Move to next left endpoint
        }
        else
        {
            current_intervals--;
            j++; // Move to next right endpoint
        }
    }

    // Display result
    printf("\n--- Result ---\n");
    printf("Point in maximum intervals: p = %d\n", best_point);
    printf("Total overlapping intervals at this point: %d\n", max_intervals);

    free(L);
    free(R);
    return 0;
}