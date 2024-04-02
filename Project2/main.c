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
    printf("Enter the size of the vectors(2^n): ");
    scanf_s("%d", &n);

    int size = (int)pow(2, n);

 
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

    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);

    double time_c_total = 0.0, time_asm_total = 0.0, time_c = 0.0, time_asm = 0.0;
    double result_c, result_asm;
    int iterations = 30; // Run 30 times

    for (int i = 0; i < iterations; i++) {
        QueryPerformanceCounter(&start);
        result_c = dot_product_c(a, b, size); 
        QueryPerformanceCounter(&end);
        time_c = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart; 
        time_c_total += time_c;
        printf("Dot product C: %lf, Time: %lf ms\n", result_c, time_c);

        QueryPerformanceCounter(&start);
        result_asm = dot_product_asm(a, b, size); 
        QueryPerformanceCounter(&end);
        time_asm = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart; 
        time_asm_total += time_asm;
        printf("Dot product asm: %lf, Time: %lf ms\n", result_asm, time_asm);
    }


    double avg_time_c = time_c_total / iterations;
    double avg_time_asm = time_asm_total / iterations;
    if (result_c == result_asm)
        printf("Dot product C and ASM results are equal\n");
    else
        printf("Dot product C and ASM results are not equal\n");
    printf("Average Dot product C time: %lf ms\n", avg_time_c);
    printf("Average Dot product ASM time: %lf ms\n", avg_time_asm);


    free(a);
    free(b);

    return 0;
}