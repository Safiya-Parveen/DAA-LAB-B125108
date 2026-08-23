#include <stdio.h>
#include <stdlib.h>

// Standard comparison for qsort
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// Function to find an element's index in an unsorted array to keep X and Y linked
void sort_intervals_by_x(int X[], int Y[], int n)
{
    // Pack X and Y into a single combined representation temporarily or use standard index sorting
    // Simple index-based approach:
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (X[i] > X[j])
            {
                // Swap start points
                int tempX = X[i];
                X[i] = X[j];
                X[j] = tempX;
                // Swap corresponding end points
                int tempY = Y[i];
                Y[i] = Y[j];
                Y[j] = tempY;
            }
        }
    }
}

int main()
{
    int n;

    printf("Enter total number of intervals (n): ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid size.\n");
        return 1;
    }

    int *X = (int *)malloc(n * sizeof(int)); // Start points
    int *Y = (int *)malloc(n * sizeof(int)); // End points

    printf("Enter intervals as x y pairs (e.g., '1 3'):\n");
    for (int i = 0; i < n; i++)
    {
        printf("Interval %d: ", i + 1);
        scanf("%d %d", &X[i], &Y[i]);
    }

    // Step 1: Sort pairs based on starting point X
    sort_intervals_by_x(X, Y, n);

    // Step 2: Merge intervals on the fly using simple variables
    printf("\n--- Merged Intervals ---\n");

    int cur_x = X[0];
    int cur_y = Y[0];

    for (int i = 1; i < n; i++)
    {
        // If current interval overlaps with (cur_x, cur_y)
        if (X[i] <= cur_y)
        {
            if (Y[i] > cur_y)
            {
                cur_y = Y[i]; // Extend current end point
            }
        }
        // No overlap -> print previous merged interval and reset tracker
        else
        {
            printf("(%d, %d) ", cur_x, cur_y);
            cur_x = X[i];
            cur_y = Y[i];
        }
    }

    // Print the last remaining interval
    printf("(%d, %d)\n", cur_x, cur_y);

    free(X);
    free(Y);
    return 0;
}