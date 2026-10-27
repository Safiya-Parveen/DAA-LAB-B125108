#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 1000
#define M 10000

int head[N], to[2 * M], wt[2 * M], next[2 * M], edges = 0;
int dist[2 * N];

typedef struct Node
{
    int x;
    struct Node *prev, *next;
} Node;

Node *front = NULL, *back = NULL;

void addEdge(int u, int v, int w)
{
    to[edges] = v;
    wt[edges] = w;
    next[edges] = head[u];
    head[u] = edges++;
}

void pushFront(int x)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->x = x;
    p->prev = NULL;
    p->next = front;
    if (front)
        front->prev = p;
    else
        back = p;
    front = p;
}

void pushBack(int x)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->x = x;
    p->next = NULL;
    p->prev = back;
    if (back)
        back->next = p;
    else
        front = p;
    back = p;
}

int popFront()
{
    Node *p = front;
    int x = p->x;
    front = front->next;
    if (front)
        front->prev = NULL;
    else
        back = NULL;
    free(p);
    return x;
}

int main()
{
    int n, m, s, C;
    scanf("%d%d%d%d", &n, &m, &s, &C);

    for (int i = 0; i < n; i++)
        head[i] = -1;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
    }

    for (int i = 0; i < 2 * n; i++)
        dist[i] = INT_MAX;

    dist[2 * s] = 0; // Source with even parity
    pushFront(2 * s);

    while (front != NULL)
    {
        int state = popFront();
        int u = state / 2;
        int parity = state % 2;

        for (int e = head[u]; e != -1; e = next[e])
        {
            int v = to[e], w = wt[e];
            int newState = 2 * v + (parity ^ w);

            if (dist[state] + w < dist[newState])
            {
                dist[newState] = dist[state] + w;

                if (w == 0)
                    pushFront(newState);
                else
                    pushBack(newState);
            }
        }
    }

    for (int v = 0; v < n; v++)
    {
        int even = dist[2 * v];
        int odd = dist[2 * v + 1];

        if (even == INT_MAX && odd == INT_MAX)
            printf("Vertex %d: Unreachable\n", v);
        else
        {
            int ans = even;
            if (odd != INT_MAX && odd + C < ans)
                ans = odd + C;

            printf("Vertex %d: %d\n", v, ans);
        }
    }

    return 0;
}