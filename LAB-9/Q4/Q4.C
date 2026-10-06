#include <stdio.h>

int heap[100];
int size = 0;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(int x)
{
    int i = size++;

    heap[i] = x;

    while (i > 0)
    {
        int p = (i - 1) / 2;

        if (heap[p] <= heap[i])
            break;

        swap(&heap[p], &heap[i]);
        i = p;
    }
}

int deleteMin()
{
    int result = heap[0];

    heap[0] = heap[--size];

    int i = 0;

    while (1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < size && heap[left] < heap[smallest])
            smallest = left;

        if (right < size && heap[right] < heap[smallest])
            smallest = right;

        if (smallest == i)
            break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }

    return result;
}

int main()
{
    int n;

    printf("Enter number of sticks: ");
    scanf("%d", &n);

    printf("Enter stick lengths:\n");

    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        insert(x);
    }

    int totalCost = 0;

    while (size > 1)
    {
        int a = deleteMin();
        int b = deleteMin();

        int newStick = a + b;

        totalCost += newStick;

        insert(newStick);
    }

    printf("Minimum total cost = %d\n", totalCost);

    return 0;
}