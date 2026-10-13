
#include <stdio.h>

#define MAX 1000

int parent[MAX], active[MAX];
int weight[MAX], sum[MAX];
int graph[MAX][MAX];

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
    sum[a] += sum[b];
}

int getMaximum(int n)
{
    int maximum = 0;

    for (int i = 0; i < n; i++)
    {
        if (active[i] && find(i) == i)
        {
            if (sum[i] > maximum)
                maximum = sum[i];
        }
    }

    return maximum;
}

int main()
{
    int n, m;
    int u, v, order[MAX], answer[MAX];

    printf("Enter vertices and edges: ");
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        sum[i] = 0;
        active[i] = 0;

        printf("Enter weight of vertex %d: ", i);
        scanf("%d", &weight[i]);
    }

    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }

    printf("Enter deletion order: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &order[i]);

    // Process deletions in reverse
    for (int i = n - 1; i >= 0; i--)
    {
        // Record the state after deletion i+1
        answer[i] = getMaximum(n);

        int x = order[i];
        active[x] = 1;
        parent[x] = x;
        sum[x] = weight[x];

        // Connect x to its active neighbours
        for (int j = 0; j < n; j++)
        {
            if (graph[x][j] && active[j])
                unite(x, j);
        }
    }

    printf("Maximum sums after each deletion:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", answer[i]);

    return 0;
}
