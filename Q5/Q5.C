
#include <stdio.h>

#define MAX 1000

int parent[MAX];

int find(int x)
{
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

void unite(int a, int b)
{
    a = find(a);
    b = find(b);

    if (a != b)
        parent[b] = a;
}

int main()
{
    int n, m, A[MAX];
    int u, v;

    printf("Enter n and m: ");
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        scanf("%d", &A[i]);
    }

    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &u, &v);
        unite(u, v);
    }

    // Process each component once
    for (int i = 0; i < n; i++)
    {
        if (find(i) != i)
            continue;

        int pos[MAX], val[MAX];
        int count = 0;

        // Collect positions and values
        for (int j = 0; j < n; j++)
        {
            if (find(j) == i)
            {
                pos[count] = j;
                val[count] = A[j];
                count++;
            }
        }

        // Sort values in ascending order
        for (int j = 0; j < count - 1; j++)
        {
            for (int k = j + 1; k < count; k++)
            {
                if (val[j] > val[k])
                {
                    int temp = val[j];
                    val[j] = val[k];
                    val[k] = temp;
                }
            }
        }

        // Positions are already collected in
        // increasing order. Assign sorted values.
        for (int j = 0; j < count; j++)
            A[pos[j]] = val[j];
    }

    printf("Smallest permutation: ");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    return 0;
}
