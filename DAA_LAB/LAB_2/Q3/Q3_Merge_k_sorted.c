#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare_ints(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}

// Merge two sorted arrays
void mergeArrays(int *A, int n1, int *B, int n2, int *C) {
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2) {
        if (A[i] <= B[j]) C[k++] = A[i++];
        else C[k++] = B[j++];
    }
    while (i < n1) C[k++] = A[i++];
    while (j < n2) C[k++] = B[j++];
}

// Method 1: Sequential merging
int* sequentialMerge(int **arrays, int k, int n) {
    int *result = malloc(n * sizeof(int));
    for (int i=0; i<n; i++) result[i] = arrays[0][i];
    int size = n;

    for (int i=1; i<k; i++) {
        int *temp = malloc((size+n) * sizeof(int));
        mergeArrays(result, size, arrays[i], n, temp);
        free(result);
        result = temp;
        size += n;
    }
    return result;
}

// Method 2: Pairwise merging
int* pairwiseMerge(int **arrays, int k, int n) {
    int size = n;
    while (k > 1) {
        int newK = (k+1)/2;
        int **newArrays = malloc(newK * sizeof(int*));
        for (int i=0; i<newK; i++) {
            if (2*i+1 < k) {
                newArrays[i] = malloc(2*size * sizeof(int));
                mergeArrays(arrays[2*i], size, arrays[2*i+1], size, newArrays[i]);
            } else {
                newArrays[i] = arrays[2*i];
            }
        }
        arrays = newArrays;
        size *= 2;
        k = newK;
    }
    return arrays[0];
}

int main() {
    int k = 8, n = 1000;
    int **arrays = malloc(k * sizeof(int*));
    srand(time(NULL));
    for (int i = 0; i < k; i++) {
        arrays[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) arrays[i][j] = rand();
        qsort(arrays[i], n, sizeof(int), compare_ints);
    }

    clock_t start = clock();
    int *res1 = sequentialMerge(arrays, k, n);
    clock_t end = clock();
    printf("Sequential Merge Time: %.6f sec\n", (double)(end-start)/CLOCKS_PER_SEC);

    start = clock();
    int *res2 = pairwiseMerge(arrays, k, n);
    end = clock();
    printf("Pairwise Merge Time: %.6f sec\n", (double)(end-start)/CLOCKS_PER_SEC);

    free(res1);
    free(res2);
    return 0;
}