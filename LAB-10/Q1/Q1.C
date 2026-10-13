
#include <stdio.h>

int graph[100][100];
int color[100];
int n;

int isBipartite()
{
    int queue[100];

    for (int i = 0; i < n; i++)
        color[i] = -1;

    for (int start = 0; start < n; start++)
    {
        if (color[start] != -1)
            continue;

        int front = 0, rear = 0;
        queue[rear++] = start;
        color[start] = 0;

        while (front < rear)
        {
            int u = queue[front++];

            for (int v = 0; v < n; v++)
            {
                if (graph[u][v] == 0)
                    continue;

                if (color[v] == -1)
                {
                    color[v] = 1 - color[u];
                    queue[rear++] = v;
                }
                else if (color[v] == color[u])
                {
                    return 0;
                }
            }
        }
    }

    return 1;
}

int main()
{
    int e, u, v;

    printf("Enter vertices and edges: ");
    scanf("%d%d", &n, &e);

    for (int i = 0; i < e; i++)
    {
        printf("Enter edge (u v): ");
        scanf("%d%d", &u, &v);

        // Temporarily add the edge
        graph[u][v] = graph[v][u] = 1;

        if (isBipartite())
        {
            printf("Edge accepted\n");
        }
        else
        {
            // Reject the edge
            graph[u][v] = graph[v][u] = 0;
            printf("Edge rejected: not bipartite\n");
        }
    }

    return 0;
}
