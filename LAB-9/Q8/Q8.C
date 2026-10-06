#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n;

    printf("Enter number of meetings: ");
    scanf("%d", &n);

    int start[n];
    int end[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter start and end time: ");
        scanf("%d %d", &start[i], &end[i]);
    }

    qsort(start, n, sizeof(int), compare);
    qsort(end, n, sizeof(int), compare);

    int i = 0;
    int j = 0;

    int rooms = 0;
    int maxRooms = 0;

    while (i < n)
    {
        if (start[i] < end[j])
        {
            rooms++;

            if (rooms > maxRooms)
                maxRooms = rooms;

            i++;
        }
        else
        {
            rooms--;
            j++;
        }
    }

    printf("Minimum number of rooms = %d\n", maxRooms);

    return 0;
}