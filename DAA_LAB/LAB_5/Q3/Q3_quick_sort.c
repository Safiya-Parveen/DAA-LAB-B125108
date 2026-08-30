#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int a[], int low, int high)
{
    int pivot = a[high];
    int i = low - 1;
    int j, temp;

    for (j = low; j < high; j++)
    {
        if (a[j] < pivot)
        {
            i++;

            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    temp = a[i + 1];
    a[i + 1] = a[high];
    a[high] = temp;

    return i + 1;
}

void quickSort(int a[], int low, int high)
{
    int p;

    if (low < high)
    {
        p = partition(a, low, high);

        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

int main()
{
    int n, i;
    int a[100];

    FILE *f;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    srand(time(NULL));

    /* Generate random numbers and store in file */
    f = fopen("input.txt", "w");

    printf("Random elements:\n");

    for (i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
        printf("%d ", a[i]);
        fprintf(f, "%d ", a[i]);
    }

    fclose(f);

    /* Read elements from file */
    f = fopen("input.txt", "r");

    for (i = 0; i < n; i++)
        fscanf(f, "%d", &a[i]);

    fclose(f);

    /* Quick Sort */
    quickSort(a, 0, n - 1);

    /* Store sorted elements */
    f = fopen("output.txt", "w");

    printf("\nSorted elements:\n");

    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
        fprintf(f, "%d ", a[i]);
    }

    fclose(f);

    return 0;
}