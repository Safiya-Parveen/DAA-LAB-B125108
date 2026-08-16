/*
Max and Min using D&C Approach: Using the divide and conquer approach, develop
an algorithm to find the maximum and minimum elements in an array of size n so that the
number of comparisons will be bounded by 3n
2
. Implement your algorithm in C to validate
the result.*/

#include <stdio.h>

struct Pair
{
    int min;
    int max;
};

struct Pair getMinMax(int arr[], int low, int high)
{
    struct Pair result, leftPair, rightPair;
    int mid;

    // Base Case 1: 1 element
    if (low == high)
    {
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }

    // Base Case 2: 2 elements
    if (high == low + 1)
    {
        if (arr[low] > arr[high])
        {
            result.max = arr[low];
            result.min = arr[high];
        }
        else
        {
            result.max = arr[high];
            result.min = arr[low];
        }
        return result;
    }

    // Divide
    mid = low + (high - low) / 2;

    // Conquer
    leftPair = getMinMax(arr, low, mid);
    rightPair = getMinMax(arr, mid + 1, high);

    // Combine
    result.max = (leftPair.max > rightPair.max) ? leftPair.max : rightPair.max;
    result.min = (leftPair.min < rightPair.min) ? leftPair.min : rightPair.min;

    return result;
}

int main()
{
    int n;
    printf("Enter the number of elements:\n");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    struct Pair minmax = getMinMax(arr, 0, n - 1);

    printf("Minimum element is: %d\n", minmax.min);
    printf("Maximum element is: %d\n", minmax.max);

    // Force output to render immediately
    fflush(stdout);

    return 0;
}