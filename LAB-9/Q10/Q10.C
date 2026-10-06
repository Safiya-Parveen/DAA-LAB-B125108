#include <stdio.h>
#include <string.h>

#define MAX 50
#define LEN 1000

int overlap(char *a, char *b)
{
    int lenA = strlen(a);
    int lenB = strlen(b);

    int max = 0;

    // Try all possible overlap lengths
    for (int k = 1; k <= lenA && k <= lenB; k++)
    {
        int same = 1;

        for (int i = 0; i < k; i++)
        {
            if (a[lenA - k + i] != b[i])
            {
                same = 0;
                break;
            }
        }

        if (same)
            max = k;
    }

    return max;
}

void mergeStrings(char *a, char *b, int overlapSize)
{
    int lenA = strlen(a);

    int lenB = strlen(b);

    for (int i = overlapSize; i < lenB; i++)
    {
        a[lenA++] = b[i];
    }

    a[lenA] = '\0';
}

int main()
{
    int n;

    printf("Enter number of strings: ");
    scanf("%d", &n);

    char s[MAX][LEN];

    for (int i = 0; i < n; i++)
    {
        printf("Enter string %d: ", i + 1);
        scanf("%s", s[i]);
    }

    // Remove strings already contained in another string
    int removed[MAX] = {0};

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j &&
                strstr(s[j], s[i]) != NULL)
            {
                removed[i] = 1;
                break;
            }
        }
    }

    // Create compact list
    char temp[MAX][LEN];
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        if (!removed[i])
        {
            strcpy(temp[count], s[i]);
            count++;
        }
    }

    // Greedy merging
    while (count > 1)
    {
        int bestI = 0;
        int bestJ = 1;
        int bestOverlap = -1;

        // Find pair with maximum overlap
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count; j++)
            {
                if (i == j)
                    continue;

                int current =
                    overlap(temp[i], temp[j]);

                if (current > bestOverlap)
                {
                    bestOverlap = current;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        // Merge bestJ into bestI
        mergeStrings(
            temp[bestI],
            temp[bestJ],
            bestOverlap);

        // Remove bestJ
        for (int i = bestJ; i < count - 1; i++)
        {
            strcpy(temp[i], temp[i + 1]);
        }

        count--;
    }

    printf("\nGreedy superstring = %s\n", temp[0]);

    return 0;
}