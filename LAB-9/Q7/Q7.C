#include <stdio.h>

int heap[100];
int size = 0;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Max heap
void insert(int x)
{
    int i = size++;

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

    heap[0] = heap[--size];

    int i = 0;

    while (1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < size && heap[left] > heap[largest])
            largest = left;

        if (right < size && heap[right] > heap[largest])
            largest = right;

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);

        i = largest;
    }

    return result;
}

int main()
{
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    int minValue = 1000000000;

    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);

        // Make every number even
        if (x % 2 != 0)
            x = x * 2;

        if (x < minValue)
            minValue = x;

        insert(x);
    }

    int answer = 1000000000;

    while (1)
    {
        int maxValue = deleteMax();

        int deviation = maxValue - minValue;

        if (deviation < answer)
            answer = deviation;

        // Largest value is odd.
        // We cannot divide it anymore.
        if (maxValue % 2 != 0)
            break;

        maxValue = maxValue / 2;

        if (maxValue < minValue)
            minValue = maxValue;

        insert(maxValue);
    }

    printf("Minimum deviation = %d\n", answer);

    return 0;
}