
#include <stdio.h>

#define MAX 1000

int parent[MAX], size[MAX];
int weight[MAX];

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

    if (a == b)
        return;

    parent[b] = a;
    size[a] += size[b];
    weight[a] += weight[b];
}

int main()
{
    int n, m, K;
    int u, v;

    printf("Enter vertices, edges and K: ");
    scanf("%d%d%d", &n, &m, &K);

    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        size[i] = 1;
        printf("Enter weight of vertex %d: ", i);
        scanf("%d", &weight[i]);
    }

    for (int e = 0; e < m; e++)
    {
        printf("Enter edge (u v): ");
        scanf("%d%d", &u, &v);

        unite(u, v);

        int maximum = -1000000000;

        for (int i = 0; i < n; i++)
        {
            if (find(i) == i && size[i] <= K)
            {
                if (weight[i] > maximum)
                    maximum = weight[i];
            }
        }

        if (maximum == -1000000000)
            printf("No eligible component\n");
        else
            printf("Maximum weight = %d\n", maximum);
    }

    return 0;
}
