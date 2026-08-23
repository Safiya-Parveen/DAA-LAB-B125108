#include <stdio.h>
#include <stdlib.h>

// Standard integer comparison function for qsort
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n;

    printf("Enter total number of persons (n): ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid size.\n");
        return 1;
    }

    int *A = (int *)malloc(n * sizeof(int)); // Entry times
    int *B = (int *)malloc(n * sizeof(int)); // Exit times

    printf("Enter entry and exit times for each person (e.g., '1 4'):\n");
    for (int k = 0; k < n; k++)
    {
        printf("Person %d: ", k + 1);
        scanf("%d %d", &A[k], &B[k]);
    }

    // Step 1: Sort both arrays independently in O(n log n)
    qsort(A, n, sizeof(int), compare);
    qsort(B, n, sizeof(int), compare);

    // Step 2: Two-pointer sweep in O(n)
    int i = 0, j = 0;
    int current_people = 0, max_people = 0, peak_time = -1;

    while (i < n && j < n)
    {
        // If next event is an ENTRY
        if (A[i] < B[j])
        {
            current_people++;
            if (current_people > max_people)
            {
                max_people = current_people;
                peak_time = A[i];
            }
            i++; // Move to next entry
        }
        // If next event is an EXIT
        else
        {
            current_people--;
            j++; // Move to next exit
        }
    }

    // Display result
    printf("\n--- Result ---\n");
    printf("Most people present simultaneously: %d\n", max_people);
    printf("Time of peak attendance: %d\n", peak_time);

    free(A);
    free(B);
    return 0;
}