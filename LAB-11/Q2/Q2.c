#include <stdio.h>

#define N 1005
#define M 20005

int head[N], to[2 * M], next[2 * M], edges = 0;
int dist[N], owner[N], q[N];

void addEdge(int u, int v)
{
    to[edges] = v;
    next[edges] = head[u];
    head[u] = edges++;
}

int main()
{
    int n, m, K, R;
    scanf("%d%d%d%d", &n, &m, &K, &R);

    for (int i = 1; i <= n; i++)
    {
        head[i] = -1;
        dist[i] = -1;
        owner[i] = -1;
    }

    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    int front = 0, back = 0;

    for (int i = 1; i <= K; i++)
    {
        int h;
        scanf("%d", &h);
        dist[h] = 0;
        owner[h] = i;
        q[back++] = h;
    }

    /* Multi-source BFS: find nearest distance */
    while (front < back)
    {
        int u = q[front++];

        for (int e = head[u]; e != -1; e = next[e])
        {
            int v = to[e];

            if (dist[v] == -1)
            {
                dist[v] = dist[u] + 1;
                q[back++] = v;
            }
        }
    }

    /* Assign the smallest-index nearest hub */
    for (int i = 0; i < back; i++)
    {
        int v = q[i];

        if (dist[v] == 0)
            continue;

        for (int e = head[v]; e != -1; e = next[e])
        {
            int u = to[e];

            if (dist[u] == dist[v] - 1 &&
                (owner[v] == -1 || owner[u] < owner[v]))
            {
                owner[v] = owner[u];
            }
        }
    }

    /* Apply the radius limit */
    for (int v = 1; v <= n; v++)
    {
        if (dist[v] == -1 || dist[v] > R)
            printf("Vertex %d: owner = -1, distance = -1\n", v);
        else
            printf("Vertex %d: owner = %d, distance = %d\n",
                   v, owner[v], dist[v]);
    }

    return 0;
}