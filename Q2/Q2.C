
#include <stdio.h>

#define MAX 10000

int parent[MAX], size[MAX], land[MAX];

int find(int x)
{
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

int unite(int a, int b)
{
    a = find(a);
    b = find(b);

    if (a == b)
        return 0;

    if (size[a] < size[b])
    {
        int temp = a;
        a = b;
        b = temp;
    }

    parent[b] = a;
    size[a] += size[b];
    return 1;
}

int main()
{
    int R, C, k;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    printf("Enter rows, columns and operations: ");
    scanf("%d%d%d", &R, &C, &k);

    int islands = 0;

    for (int i = 0; i < R * C; i++)
    {
        parent[i] = i;
        size[i] = 1;
        land[i] = 0;
    }

    for (int t = 0; t < k; t++)
    {
        int r, c;
        scanf("%d%d", &r, &c);

        // Convert to zero-based coordinates
        int x = r * C + c;

        if (land[x])
        {
            printf("%d ", islands);
            continue;
        }

        land[x] = 1;
        islands++;

        for (int d = 0; d < 4; d++)
        {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr < 0 || nr >= R ||
                nc < 0 || nc >= C)
                continue;

            int y = nr * C + nc;

            if (land[y] && unite(x, y))
                islands--;
        }

        printf("%d ", islands);
    }

    return 0;
}
