#include <stdio.h>

struct Item
{
    double value;
    double weight;
    double lambda;
};

int main()
{
    int n;
    double W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    struct Item a[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter value, weight and lambda for item %d: ", i + 1);
        scanf("%lf %lf %lf",
              &a[i].value,
              &a[i].weight,
              &a[i].lambda);
    }

    printf("Enter knapsack capacity: ");
    scanf("%lf", &W);

    double totalValue = 0;
    double time = 0;

    while (W > 0)
    {
        int best = -1;
        double bestDensity = -1e9;

        // Find item having maximum current density
        for (int i = 0; i < n; i++)
        {
            if (a[i].weight > 0)
            {
                double density =
                    a[i].value / a[i].weight - a[i].lambda * time;

                if (density > bestDensity)
                {
                    bestDensity = density;
                    best = i;
                }
            }
        }

        // No useful item left
        if (best == -1 || bestDensity <= 0)
            break;

        // Amount that can be taken
        double take;

        if (a[best].weight < W)
            take = a[best].weight;
        else
            take = W;

        totalValue += take * bestDensity;

        W -= take;
        a[best].weight -= take;

        time++;
    }

    printf("\nMaximum value = %.2lf\n", totalValue);

    return 0;
}