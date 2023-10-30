#### 12.16
```c
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
```

#### 12.17

#### 12.18

#### 12.19

#### 12.20

#### 12.21

#### 12.22

#### 12.23

#### 12.24

#### 12.25

#### 12.26

#### 12.27

#### 12.28

#### 12.29

#### 12.30

#### 12.31

#### 12.32

#### 12.33

#### 12.34

#### 12.35

#### 12.36

#### 12.37

#### 12.38

#### 12.39

