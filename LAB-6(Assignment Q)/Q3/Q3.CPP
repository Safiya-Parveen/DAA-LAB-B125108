#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void LCS(string X, string Y)
{
    int m = X.length();
    int n = Y.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Construct DP table
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Length of LCS
    cout << "Length of LCS = " << dp[m][n] << endl;

    // Find actual LCS
    string lcs = "";

    int i = m;
    int j = n;

    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs += X[i - 1];
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    reverse(lcs.begin(), lcs.end());

    cout << "LCS = " << lcs << endl;
}

int main()
{
    string X, Y;

    cout << "Enter first string: ";
    cin >> X;

    cout << "Enter second string: ";
    cin >> Y;

    LCS(X, Y);

    return 0;
}