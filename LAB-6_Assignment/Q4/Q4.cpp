#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int matrixChainMultiplication(vector<int> &arr)
{
    int n = arr.size();

    // dp[i][j] = minimum cost to multiply matrices i to j
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Length of chain
    for (int len = 2; len < n; len++)
    {
        for (int i = 1; i < n - len + 1; i++)
        {
            int j = i + len - 1;

            dp[i][j] = INT_MAX;

            for (int k = i; k < j; k++)
            {
                int cost = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];

                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[1][n - 1];
}

int main()
{
    int N;

    cout << "Enter N: ";
    cin >> N;

    vector<int> arr(N);

    cout << "Enter dimensions: ";
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    cout << "Minimum number of scalar multiplications = "
         << matrixChainMultiplication(arr);

    return 0;
}