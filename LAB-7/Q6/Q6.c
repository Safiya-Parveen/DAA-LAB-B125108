#include <stdio.h>
#include <stdlib.h>

struct Event
{
    int year;
    int type;
};

int compare(const void *a, const void *b)
{
    struct Event *x = (struct Event *)a;
    struct Event *y = (struct Event *)b;

    if (x->year != y->year)
        return x->year - y->year;

    // Death before birth
    return x->type - y->type;
}

int main()
{
    int n;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    struct Event events[2 * n];

    for (int i = 0; i < n; i++)
    {
        int birth, death;

        printf("Enter birth and death year: ");
        scanf("%d %d", &birth, &death);

        events[2 * i].year = birth;
        events[2 * i].type = 1; // birth

        events[2 * i + 1].year = death;
        events[2 * i + 1].type = 0; // death
    }

    qsort(events, 2 * n, sizeof(struct Event), compare);

    int alive = 0;
    int maximum = 0;
    int bestYear = 0;

    for (int i = 0; i < 2 * n; i++)
    {
        if (events[i].type == 0)
            alive--;
        else
            alive++;

        if (alive > maximum)
        {
            maximum = alive;
            bestYear = events[i].year;
        }
    }

    printf("Best year = %d\n", bestYear);
    printf("Maximum scientists alive = %d\n", maximum);

    return 0;
}