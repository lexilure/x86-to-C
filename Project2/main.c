#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>


extern double dot_product_asm(const double* a, const double* b, int n);

double dot_product_c(const double* a, const double* b, int n) {
    double result = 0.0;
    for (int i = 0; i < n; ++i) {
        result += a[i] * b[i];
    }
    return result;
}
int main() {
    int n;
    printf("Enter the size of the vectors (2^n): ");
    int size = (int)pow(2, n);
 
    //memory allocation
    double* a = (double*)malloc(size * sizeof(double));
    double* b = (double*)malloc(size * sizeof(double));

    if (a == NULL || b == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        a[i] = i + 1;         
        b[i] = size - i;     
    }



    // Call assembly function
    double result_asm = dot_product_asm(a, b, n);
    printf("Dot product (Assembly): %lf\n", result_asm);

    // Call C function
    double result_c = dot_product_and_measure_time(a, b, n);
    printf("Dot product (C): %lf\n", result_c);

    return 0;
}

// C function to calculate dot product and measure time

