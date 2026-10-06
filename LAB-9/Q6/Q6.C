#include <stdio.h>
#include <string.h>

struct Character
{
    char ch;
    int count;
};

struct Cooldown
{
    char ch;
    int count;
    int release;
};

struct Character heap[26];
int heapSize = 0;

void swap(struct Character *a, struct Character *b)
{
    struct Character temp = *a;
    *a = *b;
    *b = temp;
}

void insert(struct Character x)
{
    int i = heapSize++;

    heap[i] = x;

    while (i > 0)
    {
        int p = (i - 1) / 2;

        if (heap[p].count >= heap[i].count)
            break;

        swap(&heap[p], &heap[i]);

        i = p;
    }
}

struct Character deleteMax()
{
    struct Character result = heap[0];

    heap[0] = heap[--heapSize];

    int i = 0;

    while (1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < heapSize &&
            heap[left].count > heap[largest].count)
            largest = left;

        if (right < heapSize &&
            heap[right].count > heap[largest].count)
            largest = right;

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);

        i = largest;
    }

    return result;
}

int main()
{
    char s[100];

    int K;

    printf("Enter string: ");
    scanf("%s", s);

    printf("Enter K: ");
    scanf("%d", &K);

    int freq[26] = {0};

    for (int i = 0; s[i] != '\0'; i++)
        freq[s[i] - 'a']++;

    // Put all characters into max heap
    for (int i = 0; i < 26; i++)
    {
        if (freq[i] > 0)
        {
            struct Character x;

            x.ch = 'a' + i;
            x.count = freq[i];

            insert(x);
        }
    }

    struct Cooldown queue[100];

    int front = 0;
    int rear = 0;

    char answer[100];

    int position = 0;

    while (position < strlen(s))
    {
        // Release characters whose cooldown is over
        while (front < rear &&
               queue[front].release <= position)
        {
            struct Character x;

            x.ch = queue[front].ch;
            x.count = queue[front].count;

            insert(x);

            front++;
        }

        // No character available
        if (heapSize == 0)
        {
            printf("Impossible to rearrange.\n");
            return 0;
        }

        struct Character current = deleteMax();

        answer[position] = current.ch;

        current.count--;

        // Put it into cooldown
        if (current.count > 0)
        {
            queue[rear].ch = current.ch;
            queue[rear].count = current.count;
            queue[rear].release = position + K;

            rear++;
        }

        position++;
    }

    answer[position] = '\0';

    printf("Rearranged string = %s\n", answer);

    return 0;
}