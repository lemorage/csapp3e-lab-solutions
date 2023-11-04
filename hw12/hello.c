#include "csapp.h"
void *thread(void *vargp);

int main(int argc, char **argv) 
{
    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Number of threads must be a positive integer.\n");
        exit(1);
    }

    pthread_t *tids = (pthread_t *)Malloc(n * sizeof(pthread_t));
    
    for (int i = 0; i < n; ++i)
        Pthread_create(&tids[i], NULL, thread, NULL);

    for (int i = 0; i < n; ++i)
        Pthread_join(tids[i], NULL);

    Free(tids);
    exit(0);
}

void *thread(void *vargp) /* Thread routine */
{
    printf("Hello, world!\n");
    return NULL;
}
