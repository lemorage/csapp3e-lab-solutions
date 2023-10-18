#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Include the custom malloc and free functions
#include "mymemory.h"

#define NUM_ITERATIONS 1000000
#define BLOCK_SIZE 64

void benchmark_standard_malloc_free() {
    char *ptrs[NUM_ITERATIONS];
    clock_t start, end;

    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        ptrs[i] = (char *)malloc(BLOCK_SIZE);
    }

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        free(ptrs[i]);
    }
    end = clock();

    printf("Standard malloc/free: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void benchmark_custom_malloc_free() {
    char *ptrs[NUM_ITERATIONS];
    clock_t start, end;

    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        ptrs[i] = (char *)mymalloc(BLOCK_SIZE);
    }

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        myfree(ptrs[i]);
    }
    end = clock();

    printf("Custom mymalloc/myfree: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

int main() {
    // Initialize custom memory manager
    mm_init();

    benchmark_standard_malloc_free();
    benchmark_custom_malloc_free();

    return 0;
}
