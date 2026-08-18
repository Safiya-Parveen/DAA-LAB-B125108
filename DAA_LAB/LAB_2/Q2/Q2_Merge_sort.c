#include <stdio.h>

int temp[100]; // Global helper array for merging

// --------------------------------------------------
// 1. STANDARD 2-WAY MERGE SORT
// --------------------------------------------------
void merge2(int arr[], int low, int mid, int high)
{
    int i = low, j = mid + 1, k = low;

    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= high)
        temp[k++] = arr[j++];

    for (i = low; i <= high; i++)
        arr[i] = temp[i];
}

void mergeSort2(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort2(arr, low, mid);
        mergeSort2(arr, mid + 1, high);
        merge2(arr, low, mid, high);
    }
}

// --------------------------------------------------
// 2. MODIFIED 3-WAY MERGE SORT
// --------------------------------------------------
void merge3(int arr[], int low, int mid1, int mid2, int high)
{
    int i = low, j = mid1 + 1, k = mid2 + 1, l = low;

    // Compare all 3 parts
    while (i <= mid1 && j <= mid2 && k <= high)
    {
        if (arr[i] <= arr[j] && arr[i] <= arr[k])
            temp[l++] = arr[i++];
        else if (arr[j] <= arr[i] && arr[j] <= arr[k])
            temp[l++] = arr[j++];
        else
            temp[l++] = arr[k++];
    }

    // Compare remaining 2 parts if 1 becomes empty
    while (i <= mid1 && j <= mid2)
    {
        if (arr[i] <= arr[j])
            temp[l++] = arr[i++];
        else
            temp[l++] = arr[j++];
    }
    while (j <= mid2 && k <= high)
    {
        if (arr[j] <= arr[k])
            temp[l++] = arr[j++];
        else
            temp[l++] = arr[k++];
    }
    while (i <= mid1 && k <= high)
    {
        if (arr[i] <= arr[k])
            temp[l++] = arr[i++];
        else
            temp[l++] = arr[k++];
    }

    // Copy any leftover single elements
    while (i <= mid1)
        temp[l++] = arr[i++];
    while (j <= mid2)
        temp[l++] = arr[j++];
    while (k <= high)
        temp[l++] = arr[k++];

    for (i = low; i <= high; i++)
        arr[i] = temp[i];
}

void mergeSort3(int arr[], int low, int high)
{
    if (low >= high)
        return;

    int third = (high - low) / 3;
    int mid1 = low + third;
    int mid2 = low + 2 * third;

    mergeSort3(arr, low, mid1);
    mergeSort3(arr, mid1 + 1, mid2);
    mergeSort3(arr, mid2 + 1, high);

    merge3(arr, low, mid1, mid2, high);
}

// --------------------------------------------------
// MAIN
// --------------------------------------------------
int main()
{
    int n;
    printf("Enter the number of elements:\n");
    scanf("%d", &n);
    int arr1[n], arr2[n];
    printf("Enter the elements for array 1:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr1[i]);
    }

    printf("Enter the elements for array 2:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr2[i]);
    }

    mergeSort2(arr1, 0, n - 1);
    mergeSort3(arr2, 0, n - 1);

    printf("2-Way Sorted: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr1[i]);

    printf("\n3-Way Sorted: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr2[i]);

    return 0;
}