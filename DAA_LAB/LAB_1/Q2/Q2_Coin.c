/*Fair vs Biased coin: Using simulation in C, show that the probability of getting a HEAD by tossing a
 fair coin is about 0.5. Extend your simulation to compare fair vs biased coin-tossing experiments.
 [Interesting Read] Check this article on arXiv titled “Random Coin Tossing with unknown bias” for more insight.*/

#include <stdio.h>
#include <stdlib.h>

// function for fair coin

int fairCoin(int n)
{
    int head = 0;
    for (int i = 0; i < n; i++)
    {
        int toss = rand() % 2;
        if (toss == 0)
        {
            head++;
        }
    }
    printf("probability of head in fair coin = %f\n", (double)head / n);
}

// FUNCTION FOR BIASED COIN

int biasedCoin(int n)
{
    int head = 0;
    for (int i = 0; i < n; i++)
    {
        int toss = rand() / RAND_MAX;
        if (toss < 0.9)
        {
            head++;
        }
    }
    printf("probability of head in biased coin = %f\n", (double)head / n);
}
int main()
{
    int n = 10000;
    fairCoin(n);
    biasedCoin(n);
    return 0;
}