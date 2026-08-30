#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void heapify(int a[], int n, int i)
{
    int largest;
    int left, right;
    int temp;

    largest = i;
    left = 2 * i + 1;
    right = 2 * i + 2;

    if (left < n && a[left] > a[largest])
        largest = left;

    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i)
    {
        temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;

        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    int i, temp;

    /* Build max heap */
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    /* Sort */
    for (i = n - 1; i > 0; i--)
    {
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        heapify(a, i, 0);
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

    /* Heap Sort */
    heapSort(a, n);

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