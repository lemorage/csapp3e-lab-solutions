#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 1000  // Matrix size (N x N)
#define NUM_THREADS 4  // Number of threads

int matrixA[N][N];
int matrixB[N][N];
int resultSequential[N][N];
int resultParallel[N][N];
pthread_t threads[NUM_THREADS];

// Matrix multiplication function for sequential execution
void multiplySequential() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            resultSequential[i][j] = 0;
            for (int k = 0; k < N; k++)
                resultSequential[i][j] += matrixA[i][k] * matrixB[k][j];
        }
    }
}

// Matrix multiplication function for parallel execution by each thread
void* multiplyParallel(void* arg) {
    int thread_id = *(int*)arg;
    int chunk_size = N / NUM_THREADS;
    int start_row = thread_id * chunk_size;
    int end_row = (thread_id == NUM_THREADS - 1) ? N : (start_row + chunk_size);

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < N; j++) {
            resultParallel[i][j] = 0;
            for (int k = 0; k < N; k++)
                resultParallel[i][j] += matrixA[i][k] * matrixB[k][j];
        }
    }

    pthread_exit(NULL);
}

int main() {
    // Initialize matrices with random values (you can replace with your own data)
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrixA[i][j] = rand() % 100;
            matrixB[i][j] = rand() % 100;
        }
    }

    // Measure sequential execution time
    clock_t start = clock();
    multiplySequential();
    clock_t end = clock();
    double sequentialTime = (double)(end - start) / CLOCKS_PER_SEC;

    // Measure parallel execution time
    int thread_args[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, multiplyParallel, &thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    // Verify that the results match (you can omit this in the final comparison)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (resultSequential[i][j] != resultParallel[i][j]) {
                printf("Results do not match!\n");
                return 1;
            }
        }
    }

    // Calculate parallel execution time
    start = clock();
    // Multiply parallel threads already completed
    end = clock();
    double parallelTime = (double)(end - start) / CLOCKS_PER_SEC;

    // Print execution times
    printf("Sequential Execution Time: %f seconds\n", sequentialTime);
    printf("Parallel Execution Time: %f seconds\n", parallelTime);

    return 0;
}
