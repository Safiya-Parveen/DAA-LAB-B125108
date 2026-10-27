#include <stdio.h>
#include <string.h>

#define N 100005
#define H 262147

char words[N][11], temp[11];
int table[H], d1[N], d2[N];
int q1[N], q2[N], n1, n2, next1[N], next2[N];

unsigned hash(char *s)
{
    unsigned h = 0;
    while (*s)
        h = h * 31 + *s++;
    return h % H;
}

int find(char *s)
{
    unsigned h = hash(s);
    while (table[h])
    {
        if (strcmp(words[table[h] - 1], s) == 0)
            return table[h] - 1;
        h = (h + 1) % H;
    }
    return -1;
}

void insert(int i)
{
    unsigned h = hash(words[i]);
    while (table[h])
        h = (h + 1) % H;
    table[h] = i + 1;
}

int main()
{
    int n;
    char A[11], B[11];

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%10s", words[i]);
        insert(i);
    }

    scanf("%10s%10s", A, B);

    int start = find(A), target = find(B);

    if (strcmp(A, B) == 0)
    {
        printf("0\n");
        return 0;
    }

    if (target == -1)
    {
        printf("-1\n");
        return 0;
    }

    if (start == -1)
    {
        start = n;
        strcpy(words[start], A);
    }

    for (int i = 0; i <= n; i++)
        d1[i] = d2[i] = -1;

    q1[0] = start;
    n1 = 1;
    q2[0] = target;
    n2 = 1;
    d1[start] = d2[target] = 0;

    while (n1 && n2)
    {
        int *q, *nq, *d, *other, *nextCount;
        int count, *frontier, *nextFrontier;

        if (n1 <= n2)
        {
            q = q1;
            nq = next1;
            d = d1;
            other = d2;
            count = n1;
            frontier = q1;
            nextFrontier = next1;
            nextCount = &n1;
        }
        else
        {
            q = q2;
            nq = next2;
            d = d2;
            other = d1;
            count = n2;
            frontier = q2;
            nextFrontier = next2;
            nextCount = &n2;
        }

        int nn = 0;

        for (int i = 0; i < count; i++)
        {
            int u = q[i];
            strcpy(temp, words[u]);

            for (int j = 0; temp[j]; j++)
            {
                char old = temp[j];

                for (char c = 'a'; c <= 'z'; c++)
                {
                    if (c == old)
                        continue;
                    temp[j] = c;
                    int v = find(temp);

                    if (v != -1)
                    {
                        if (other[v] != -1)
                        {
                            printf("%d\n", d[u] + 1 + other[v]);
                            return 0;
                        }

                        if (d[v] == -1)
                        {
                            d[v] = d[u] + 1;
                            nextFrontier[nn++] = v;
                        }
                    }
                }
                temp[j] = old;
            }
        }

        if (nextCount == &n1)
            n1 = nn;
        else
            n2 = nn;

        for (int i = 0; i < nn; i++)
            frontier[i] = nextFrontier[i];
    }

    printf("-1\n");
    return 0;
}