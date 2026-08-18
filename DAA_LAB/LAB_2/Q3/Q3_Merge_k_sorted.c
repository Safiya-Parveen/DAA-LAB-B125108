#include <stdio.h>
#include <stdlib.h>

// Standard 2-array merge helper subroutine
void mergeTwo(int *a, int size_a, int *b, int size_b, int *result)
{
    int i = 0, j = 0, k = 0;

    while (i < size_a && j < size_b)
    {
        if (a[i] <= b[j])
        {
            result[k++] = a[i++];
        }
        else
        {
            result[k++] = b[j++];
        }
    }

    while (i < size_a)
        result[k++] = a[i++];
    while (j < size_b)
        result[k++] = b[j++];
}

// Method 2: Pairwise reduction of k sorted arrays
int *mergeKPairs(int **arrays, int k, int n, int *total_len)
{
    int current_k = k;
    int current_n = n;

    // Create a working array of pointers
    int **current_arrays = (int **)malloc(current_k * sizeof(int *));
    if (current_arrays == NULL)
        return NULL;

    for (int i = 0; i < current_k; i++)
    {
        current_arrays[i] = arrays[i];
    }

    // Process until only 1 single array remains
    while (current_k > 1)
    {
        int next_k = (current_k + 1) / 2;
        int **next_arrays = (int **)malloc(next_k * sizeof(int *));
        if (next_arrays == NULL)
            return NULL;

        int out_idx = 0;

        for (int i = 0; i < current_k; i += 2)
        {
            if (i + 1 < current_k)
            {
                // Pair arrays i and i+1 into a combined array of size 2 * current_n
                int *merged = (int *)malloc(2 * current_n * sizeof(int));
                mergeTwo(current_arrays[i], current_n, current_arrays[i + 1], current_n, merged);
                next_arrays[out_idx++] = merged;

                // Free intermediate merged arrays from previous rounds
                if (current_n > n)
                {
                    free(current_arrays[i]);
                    free(current_arrays[i + 1]);
                }
            }
            else
            {
                // Odd array left out: pass it straight to the next round
                next_arrays[out_idx++] = current_arrays[i];
            }
        }

        free(current_arrays);
        current_arrays = next_arrays;
        current_k = next_k;
        current_n *= 2;
    }

    *total_len = k * n;
    int *final_result = current_arrays[0];
    free(current_arrays);

    return final_result;
}

int main()
{
    int k = 4; // Number of arrays
    int n = 3; // Length of each array

    // Sample static data for testing
    int sampleData[4][3] = {
        {1, 5, 9},
        {2, 6, 10},
        {3, 4, 11},
        {7, 8, 12}};

    // Dynamic 2D Array allocation
    int **arrays = (int *)malloc(k * sizeof(int *));
    if (arrays == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < k; i++)
    {
        arrays[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
        {
            arrays[i][j] = sampleData[i][j];
        }
    }

    // Print initial input
    printf("Input Sorted Arrays:\n");
    for (int i = 0; i < k; i++)
    {
        printf("Array %d: ", i + 1);
        for (int j = 0; j < n; j++)
        {
            printf("%d ", arrays[i][j]);
        }
        printf("\n");
    }

    // Execute Method 2 Pairwise Merge
    int total_len = 0;
    int *sorted = mergeKPairs(arrays, k, n, &total_len);

    // Output final result
    printf("\nMerged Array (Length %d):\n", total_len);
    for (int i = 0; i < total_len; i++)
    {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    // Cleanup initial dynamic allocations
    for (int i = 0; i < k; i++)
    {
        free(arrays[i]);
    }
    free(arrays);
    free(sorted);

    return 0;
}