#include <stdio.h>
#include <stdlib.h>

// Helper to allocate an n x n dynamic 2D array
double **create_matrix(int n)
{
    double **mat = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        mat[i] = (double *)malloc(n * sizeof(double));
    }
    return mat;
}

// Helper to free memory of an n x n array
void free_matrix(double **mat, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(mat[i]);
    }
    free(mat);
}

// Core Divide & Conquer algorithm
void multiply_special(double **A, double **B, double **C,
                      int rA, int cA, int rB, int cB, int rC, int cC, int size)
{
    // Base Case: Single element (1x1)
    if (size == 1)
    {
        C[rC][cC] = A[rA][cA] * B[rB][cB];
        return;
    }

    int k = size / 2;

    // Allocate temporary sub-matrices for calculation
    double **S1 = create_matrix(k);
    double **S2 = create_matrix(k);
    double **D1 = create_matrix(k);
    double **D2 = create_matrix(k);
    double **P1 = create_matrix(k);
    double **P2 = create_matrix(k);

    // Step 1: Compute S1 = A1 + A2, S2 = B1 + B2, D1 = A1 - A2, D2 = B1 - B2
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            S1[i][j] = A[rA + i][cA + j] + A[rA + i][cA + j + k];
            D1[i][j] = A[rA + i][cA + j] - A[rA + i][cA + j + k];

            S2[i][j] = B[rB + i][cB + j] + B[rB + i][cB + j + k];
            D2[i][j] = B[rB + i][cB + j] - B[rB + i][cB + j + k];
        }
    }

    // Step 2: ONLY TWO recursive multiplications
    multiply_special(S1, S2, P1, 0, 0, 0, 0, 0, 0, k);
    multiply_special(D1, D2, P2, 0, 0, 0, 0, 0, 0, k);

    // Step 3: Compute C1 & C2 and directly write them into Matrix C
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            double c1 = 0.5 * (P1[i][j] + P2[i][j]);
            double c2 = 0.5 * (P1[i][j] - P2[i][j]);

            C[rC + i][cC + j] = c1;         // Top-Left (C1)
            C[rC + i][cC + j + k] = c2;     // Top-Right (C2)
            C[rC + i + k][cC + j] = c2;     // Bottom-Left (C2)
            C[rC + i + k][cC + j + k] = c1; // Bottom-Right (C1)
        }
    }

    // Free intermediate temporary matrices
    free_matrix(S1, k);
    free_matrix(S2, k);
    free_matrix(D1, k);
    free_matrix(D2, k);
    free_matrix(P1, k);
    free_matrix(P2, k);
}

// Function to print a matrix
void print_matrix(double **mat, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%7.2f ", mat[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int n;

    printf("Enter the size of the matrix n (must be a power of 2, e.g., 2, 4, 8): ");
    scanf("%d", &n);

    // Simple check for power of 2
    if (n <= 0 || (n & (n - 1)) != 0)
    {
        printf("Error: Matrix size must be a power of 2 (2, 4, 8, 16...)\n");
        return 1;
    }

    // Allocate matrices based on user input size
    double **A = create_matrix(n);
    double **B = create_matrix(n);
    double **C = create_matrix(n);

    // User input for Matrix A
    printf("\nEnter elements for Matrix A (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("A[%d][%d]: ", i, j);
            scanf("%lf", &A[i][j]);
        }
    }

    // User input for Matrix B
    printf("\nEnter elements for Matrix B (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("B[%d][%d]: ", i, j);
            scanf("%lf", &B[i][j]);
        }
    }

    // Perform Multiplication
    multiply_special(A, B, C, 0, 0, 0, 0, 0, 0, n);

    // Display Result
    printf("\n--- Result Matrix C (A * B) ---\n");
    print_matrix(C, n);

    // Clean up memory
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);

    return 0;
}