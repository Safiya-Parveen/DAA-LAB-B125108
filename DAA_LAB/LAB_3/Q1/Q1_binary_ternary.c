#include <stdio.h>

int binarySearch(int low, int high, int key, int arr[])
{
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (key == arr[mid])
            return mid;
        if (key < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

int ternarySearch(int low, int high, int key, int arr[])
{
    while (low <= high)
    {
        int third = (high - low) / 3;
        int mid1 = low + third;
        int mid2 = high - third;
        if (key == arr[mid1])
        {
            return mid1;
        }
        if (key == arr[mid2])
        {
            return mid2;
        }
        if (key < mid1)
            high = mid1 - 1;
        if (key > mid2)
            low = mid2 + 1;
    }
    return -1;
}

int main()
{
    int n;
    printf("Enter the n0. of elements\n");
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("Enter the value of the key\n");
    int key;
    scanf("%d", &key);

    int b = binarySearch(0, n - 1, key, arr);
    int t = ternarySearch(0, n - 1, key, arr);

    printf("Through binary search the key is at %d\n", b);
    printf("Through binary search the key is at %d \n", t);
    return 0;
}