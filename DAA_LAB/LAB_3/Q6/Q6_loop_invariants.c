#include <stdio.h>
#include <stdlib.h>

void selection_sort(int A[], int n)
{
    int comparisons = 0;
    int swaps = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            comparisons++;
            if (A[j] < A[min_idx])
            {
                min_idx = j;
            }
        }

        // Swap elements if minimum is not at index i
        if (min_idx != i)
        {
            int temp = A[i];
            A[i] = A[min_idx];
            A[min_idx] = temp;
            swaps++;
        }
    }
    printf("\nTotal Comparisons: %d\n", comparisons);
    printf("Total Swaps:       %d\n", swaps);
}

void print_array(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main()
{
    int n;
    long long comparisons, swaps;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid input size.\n");
        return 1;
    }

    int *A = (int *)malloc(n * sizeof(int));
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }

    printf("\nOriginal Array:\n");
    print_array(A, n);

    selection_sort(A, n);

    printf("\nSorted Array:\n");
    print_array(A, n);

    free(A);
    return 0;
}