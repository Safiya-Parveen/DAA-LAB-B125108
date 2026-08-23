/*Application of sorting-I: Assume that we are given n pairs of items as input, where the
first item is a number and the second item is one of three colours (red, blue, or yellow).
Further assume that the items are sorted by number. Give an O(n) algorithm to sort
the items by colour (all reds before all blues before all yellows) such that the numbers for
identical colours stay sorted. By choosing the proper input representation, write a program
in C to validate your algorithm.*/

#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLUE 1
#define YELLOW 2

typedef struct
{
    int number;
    int color; // 0 for RED, 1 for BLUE, 2 for YELLOW
} Item;

void sort_by_color(Item arr[], int n)
{
    Item *output = (Item *)malloc(n * sizeof(Item));
    int counts[3] = {0, 0, 0};

    // Step 1: Count color occurrences
    for (int i = 0; i < n; i++)
    {
        counts[arr[i].color]++;
    }

    // Step 2: Compute starting indices
    int pos[3];
    pos[RED] = 0;
    pos[BLUE] = counts[RED];
    pos[YELLOW] = counts[RED] + counts[BLUE];

    // Step 3: Stable placement into output array
    for (int i = 0; i < n; i++)
    {
        int color = arr[i].color;
        output[pos[color]] = arr[i];
        pos[color]++;
    }

    // Step 4: Copy back to original array
    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }

    free(output);
}

int main()
{
    int n;

    printf("Enter total number of items: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid input size.\n");
        return 1;
    }

    Item *arr = (Item *)malloc(n * sizeof(Item));

    printf("\nColor options:\n 0 = RED\n 1 = BLUE\n 2 = YELLOW\n\n");

    for (int i = 0; i < n; i++)
    {
        printf("Item %d - Enter number and color (e.g., '10 0' for 10 RED): ", i + 1);
        scanf("%d %d", &arr[i].number, &arr[i].color);

        // Basic input validation for color range
        while (arr[i].color < 0 || arr[i].color > 2)
        {
            printf("Invalid color! Re-enter color (0=RED, 1=BLUE, 2=YELLOW) for number %d: ", arr[i].number);
            scanf("%d", &arr[i].color);
        }
    }

    // Perform stable O(n) sort
    sort_by_color(arr, n);

    // Display sorted output
    printf("\n--- Sorted Output (Reds -> Blues -> Yellows) ---\n");
    for (int i = 0; i < n; i++)
    {
        char *color_str = (arr[i].color == RED) ? "RED" : (arr[i].color == BLUE) ? "BLUE"
                                                                                 : "YELLOW";
        printf("(%d, %s)\n", arr[i].number, color_str);
    }

    free(arr);
    return 0;
}