#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsack(int n, int W, vector<int>& weight, vector<int>& profit)
{
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int w = 1; w <= W; w++)
        {
            if (weight[i - 1] <= w)
            {
                dp[i][w] = max(
                    profit[i - 1] + dp[i - 1][w - weight[i - 1]],
                    dp[i - 1][w]
                );
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];
}

int main()
{
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    cout << "Enter capacity of knapsack: ";
    cin >> W;

    vector<int> weight(n), profit(n);

    cout << "Enter weights:\n";
    for (int i = 0; i < n; i++)
        cin >> weight[i];

    cout << "Enter profits:\n";
    for (int i = 0; i < n; i++)
        cin >> profit[i];

    cout << "Maximum Profit = "
         << knapsack(n, W, weight, profit);

    return 0;
}