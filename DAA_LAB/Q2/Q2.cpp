#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int A[10][10], B[10][10];

    cout << "Enter Matrix A:\n";

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

    cout << "Enter Matrix B:\n";

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> B[i][j];

    // 1. Matrix Addition
    cout << "\nMatrix Addition:\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << A[i][j] + B[i][j] << " ";

        cout << endl;
    }

    // 2. Matrix Multiplication
    cout << "\nMatrix Multiplication:\n";

    int C[10][10] = {0};

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];

            cout << C[i][j] << " ";
        }

        cout << endl;
    }

    // 3. Check Zero Matrix
    bool zero = true;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (A[i][j] != 0)
                zero = false;
        }
    }

    cout << "\nZero Matrix: ";

    if (zero)
        cout << "Yes\n";
    else
        cout << "No\n";

    // 4. Check Symmetric
    bool symmetric = true;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (A[i][j] != A[j][i])
                symmetric = false;
        }
    }

    cout << "Symmetric Matrix: ";

    if (symmetric)
        cout << "Yes\n";
    else
        cout << "No\n";

    // 5. Determinant
    // Simple calculation for 2x2 matrix
    if (n == 2)
    {
        int det = A[0][0] * A[1][1] - A[0][1] * A[1][0];

        cout << "Determinant = " << det << endl;
    }

    // 6. Transpose in-place
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            swap(A[i][j], A[j][i]);
        }
    }

    cout << "\nTranspose:\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << A[i][j] << " ";

        cout << endl;
    }

    return 0;
}