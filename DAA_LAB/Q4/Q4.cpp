#include <iostream>
#include <algorithm>
using namespace std;

void reversePart(int a[], int i, int j)
{
    while (i < j)
    {
        swap(a[i], a[j]);
        i++;
        j--;
    }
}

int main()
{
    int n;
    cin >> n;

    int a[100];

    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n; i++)
    {
        // Find i+1
        int pos = i;

        for (int j = i; j < n; j++)
        {
            if (a[j] == i + 1)
            {
                pos = j;
                break;
            }
        }

        // Reverse it into correct position
        if (pos != i)
            reversePart(a, i, pos);
    }

    cout << "Sorted array: ";

    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    return 0;
}