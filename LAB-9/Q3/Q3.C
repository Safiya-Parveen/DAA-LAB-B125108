#include <stdio.h>
#include <stdlib.h>

struct Station
{
    int distance;
    int fuel;
};

/* ---------- MAX HEAP ---------- */

int heap[100];
int heapSize = 0;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(int x)
{
    int i = heapSize++;

    heap[i] = x;

    while (i > 0)
    {
        int p = (i - 1) / 2;

        if (heap[p] >= heap[i])
            break;

        swap(&heap[p], &heap[i]);

        i = p;
    }
}

int deleteMax()
{
    int result = heap[0];

    heap[0] = heap[--heapSize];

    int i = 0;

    while (1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < heapSize &&
            heap[left] > heap[largest])
            largest = left;

        if (right < heapSize &&
            heap[right] > heap[largest])
            largest = right;

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);

        i = largest;
    }

    return result;
}

int compare(const void *a, const void *b)
{
    struct Station *x = (struct Station *)a;
    struct Station *y = (struct Station *)b;

    return x->distance - y->distance;
}

int main()
{
    int n, D, F;

    printf("Enter target distance: ");
    scanf("%d", &D);

    printf("Enter initial fuel: ");
    scanf("%d", &F);

    printf("Enter number of stations: ");
    scanf("%d", &n);

    struct Station s[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter distance and fuel: ");
        scanf("%d %d", &s[i].distance, &s[i].fuel);
    }

    qsort(s, n, sizeof(struct Station), compare);

    int currentFuel = F;
    int i = 0;
    int stops = 0;

    while (currentFuel < D)
    {
        // Add all reachable stations
        while (i < n && s[i].distance <= currentFuel)
        {
            insert(s[i].fuel);
            i++;
        }

        // No station can help
        if (heapSize == 0)
        {
            printf("Target cannot be reached.\n");
            return 0;
        }

        // Take maximum fuel
        currentFuel += deleteMax();

        stops++;
    }

    printf("Minimum refueling stops = %d\n", stops);

    return 0;
}