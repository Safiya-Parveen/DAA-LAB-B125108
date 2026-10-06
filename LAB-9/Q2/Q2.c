#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node
{
    int weight;
    int parent;
};

struct Symbol
{
    char ch;
    int length;
};

/* ---------- MIN HEAP ---------- */

int heap[MAX];
int heapSize = 0;

struct Node node[MAX * 2];

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertHeap(int x)
{
    int i = heapSize++;

    heap[i] = x;

    while (i > 0)
    {
        int p = (i - 1) / 2;

        if (node[heap[p]].weight <= node[heap[i]].weight)
            break;

        swap(&heap[p], &heap[i]);
        i = p;
    }
}

int deleteMin()
{
    int result = heap[0];

    heap[0] = heap[--heapSize];

    int i = 0;

    while (1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heapSize &&
            node[heap[left]].weight < node[heap[smallest]].weight)
            smallest = left;

        if (right < heapSize &&
            node[heap[right]].weight < node[heap[smallest]].weight)
            smallest = right;

        if (smallest == i)
            break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }

    return result;
}

int compareSymbols(const void *a, const void *b)
{
    struct Symbol *x = (struct Symbol *)a;
    struct Symbol *y = (struct Symbol *)b;

    if (x->length != y->length)
        return x->length - y->length;

    return x->ch - y->ch;
}

void printCode(int code, int length)
{
    for (int i = length - 1; i >= 0; i--)
        printf("%d", (code >> i) & 1);
}

int main()
{
    int n;

    printf("Enter number of symbols: ");
    scanf("%d", &n);

    char ch[n];
    int freq[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter symbol and frequency: ");
        scanf(" %c %d", &ch[i], &freq[i]);
    }

    // Create leaf nodes
    for (int i = 0; i < n; i++)
    {
        node[i].weight = freq[i];
        node[i].parent = -1;

        insertHeap(i);
    }

    int totalNodes = n;

    // Huffman construction
    while (heapSize > 1)
    {
        int a = deleteMin();
        int b = deleteMin();

        node[totalNodes].weight =
            node[a].weight + node[b].weight;

        node[totalNodes].parent = -1;

        node[a].parent = totalNodes;
        node[b].parent = totalNodes;

        insertHeap(totalNodes);

        totalNodes++;
    }

    struct Symbol symbols[n];

    // Find code length of every symbol
    for (int i = 0; i < n; i++)
    {
        int length = 0;
        int current = i;

        while (node[current].parent != -1)
        {
            length++;
            current = node[current].parent;
        }

        // Single symbol case
        if (length == 0)
            length = 1;

        symbols[i].ch = ch[i];
        symbols[i].length = length;
    }

    // Canonical ordering:
    // first by length, then lexicographically
    qsort(symbols, n, sizeof(struct Symbol), compareSymbols);

    printf("\nCanonical Huffman Codes:\n");

    int code = 0;
    int previousLength = 0;

    for (int i = 0; i < n; i++)
    {
        int length = symbols[i].length;

        code = code << (length - previousLength);

        printf("%c : ", symbols[i].ch);
        printCode(code, length);
        printf("\n");

        code++;
        previousLength = length;
    }

    return 0;
}