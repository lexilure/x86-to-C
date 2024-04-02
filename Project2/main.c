#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Assembly function prototype
extern double dot_product_asm(const double* a, const double* b, int n);

// Function prototype
double dot_product_and_measure_time(const double* a, const double* b, int n);

int main() {
    // Example vectors
    const int n = 5;
    double a[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    double b[5] = { 5.0, 4.0, 3.0, 2.0, 1.0 };

    // Print example vectors
    printf("Example vectors:\n");
    printf("Vector A: ");
    for (int i = 0; i < n; i++) {
        printf("%lf ", a[i]);
    }
    printf("\n");
    printf("Vector B: ");
    for (int i = 0; i < n; i++) {
        printf("%lf ", b[i]);
    }
    printf("\n");

    // Call assembly function
    double result_asm = dot_product_asm(a, b, n);
    printf("Dot product (Assembly): %lf\n", result_asm);

    // Call C function
    double result_c = dot_product_and_measure_time(a, b, n);
    printf("Dot product (C): %lf\n", result_c);

    return 0;
}

// C function to calculate dot product and measure time
double dot_product_and_measure_time(const double* a, const double* b, int n) {
    LARGE_INTEGER frequency, start, end;
    double result = 0.0;
    double time;

    int size;
    printf("Enter the length of the vectors: ");
    scanf_s("%d", &size);

    double* A = (double*)malloc(size * sizeof(double));
    double* B = (double*)malloc(size * sizeof(double));

    // Check if memory allocation succeeded
    if (A == NULL || B == NULL) {
        printf("Memory allocation failed\n");
        return 0.0;
    }

    printf("Enter the elements of vector A: ");
    for (int i = 0; i < size; i++) {
        scanf_s("%lf", &A[i]);
    }

    printf("Enter the elements of vector B: ");
    for (int i = 0; i < size; i++) {
        scanf_s("%lf", &B[i]);
    }

    // Get the frequency for the high-resolution performance counter
    QueryPerformanceFrequency(&frequency);

    // Measure execution time
    QueryPerformanceCounter(&start);

    // Calculate dot product
    for (int i = 0; i < size; ++i) {
        result += A[i] * B[i];
    }

    QueryPerformanceCounter(&end);
    time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Time taken by C function: %f seconds\n", time);

    free(A);
    free(B);

    return result;
}
