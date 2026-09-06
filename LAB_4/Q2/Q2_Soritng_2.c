/*Given two sets S1 and S2 (each of size n), and a number x,
describe an O(n · log n) algorithm for finding whether there exists a pair of elements, one
from S1 and one from S2, that add up to x. By choosing the proper input representation,
write a program in C to validate your algorithm.*/

#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int find_pair(int S1[], int S2[], int n, int x)
{
    qsort(S2, n, sizeof(int), compare);

    for (int i = 0; i < n; i++)
    {
        int target = x - S1[i];
        int *found = (int *)bsearch(&target, S2, n, sizeof(int), compare);

        if (found != NULL)
        {
            printf("\n--> Pair Found: %d (from S1) + %d (from S2) = %d\n", S1[i], *found, x);
            return 1;
        }
    }
    return 0;
}

int main()
{
    int n, x;

    printf("Enter size of sets (n): ");
    scanf("%d", &n);

    int *S1 = (int *)malloc(n * sizeof(int));
    int *S2 = (int *)malloc(n * sizeof(int));

    printf("Enter %d elements for Set S1: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &S1[i]);

    printf("Enter %d elements for Set S2: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &S2[i]);

    printf("Enter target sum (x): ");
    scanf("%d", &x);

    if (!find_pair(S1, S2, n, x))
    {
        printf("\n--> No pair from S1 and S2 adds up to %d\n", x);
    }

    free(S1);
    free(S2);
    return 0;
}