#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
using namespace std;

const double PI = acos(-1);

typedef complex<double> cd;

// FFT
void fft(vector<cd> &a, bool invert)
{
    int n = a.size();

    if (n == 1)
        return;

    vector<cd> even(n / 2), odd(n / 2);

    for (int i = 0; i < n / 2; i++)
    {
        even[i] = a[2 * i];
        odd[i] = a[2 * i + 1];
    }

    fft(even, invert);
    fft(odd, invert);

    double angle = 2 * PI / n;

    if (invert)
        angle = -angle;

    cd w(1);
    cd wn(cos(angle), sin(angle));

    for (int i = 0; i < n / 2; i++)
    {
        cd u = even[i];
        cd v = w * odd[i];

        a[i] = u + v;
        a[i + n / 2] = u - v;

        w *= wn;
    }

    if (invert)
    {
        for (int i = 0; i < n; i++)
            a[i] /= 2;
    }
}

// Convolution
vector<int> convolution(vector<int> A, vector<int> B)
{
    int size = 1;

    while (size < A.size() + B.size())
        size *= 2;

    A.resize(size);
    B.resize(size);

    vector<cd> a(A.begin(), A.end());
    vector<cd> b(B.begin(), B.end());

    fft(a, false);
    fft(b, false);

    for (int i = 0; i < size; i++)
        a[i] *= b[i];

    fft(a, true);

    vector<int> C(A.size() + B.size() - 1);

    for (int i = 0; i < C.size(); i++)
        C[i] = round(a[i].real());

    return C;
}

int main()
{
    int m, n;

    cin >> m >> n;

    vector<int> A(m), B(n);

    for (int i = 0; i < m; i++)
        cin >> A[i];

    for (int i = 0; i < n; i++)
        cin >> B[i];

    vector<int> C = convolution(A, B);

    cout << "Convolution: ";

    for (int x : C)
        cout << x << " ";

    return 0;
}