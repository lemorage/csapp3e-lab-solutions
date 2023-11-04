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
A. The problem with the code is that the `exit(0);` statement in the `main` function is immediately terminating the entire program, including the main thread, as soon as the thread is created.

B. To fix this bug, we should replace the `exit(0);` statement with other Pthreads function calls. The two common approaches are:

1. `pthread_join`: This function waits for the specified thread (in this case, `tid`) to finish.

```c
int main()
{
    pthread_t tid;

    Pthread_create(&tid, NULL, thread, NULL);
    Pthread_join(tid, NULL); // Wait for the thread to finish
    exit(0);
}
```

2. `pthread_exit`: This function allows the main thread to exit while other threads continue to run.

```c
int main()
{
    pthread_t tid;

    Pthread_create(&tid, NULL, thread, NULL);
    pthread_exit(NULL); // Main thread exits while the other thread continues
}
```

#### 12.18
A. Unsafe\
B. Safe\
C. Unsafe

#### 12.19
```c
/* Global variables */
int readcnt;    /* Initially = 0 */
int writecnt;   /* Initially = 0 */
sem_t mutex, w, reader_sem; /* All initially = 1 */

void reader(void)
{
    while (1) {
        P(&mutex);
        if (writecnt > 0) {
            /* If a writer is writing or waiting, let's wait */
            V(&mutex);
            P(&reader_sem);
        }
        readcnt++;
        if (readcnt == 1) /* First in */
            P(&w);
        V(&mutex);

        /* Critical section */
        /* Reading happens  */

        P(&mutex);
        readcnt--;
        if (readcnt == 0) /* Last out */
            V(&w);
        V(&mutex);
    }
}

void writer(void)
{
    while (1) {
        P(&mutex);
        writecnt++;
        if (readcnt > 0 || writecnt > 1) {
            /* If readers are reading or another writer is writing, wait */
            V(&mutex);
            P(&reader_sem);
        } else {
            V(&mutex);

            P(&w);

            /* Critical section */
            /* Writing happens  */

            V(&w);

            P(&mutex);
            writecnt--;
            /* Release waiting readers if any */
            V(&reader_sem);
            V(&mutex);
        }
    }
}
```

#### 12.20
The idea is to allow access to either readers or writers but not both at the same time. We use a single counting semaphore (`mutex`) to control access to the shared resource. Readers and writers both need to acquire this semaphore. The `pthread_mutex` (`rw_mutex`) is used to protect the `readers` counter.

```c
#include "csapp.h"

#define N some_num // Maximum number of readers

sem_t mutex;
pthread_mutex_t rw_mutex;
int readers = 0; // Number of active readers

void reader(void) {
    while (1) {
        P(&rw_mutex);
        if (readers == 0) {
            P(&mutex); // If this is the first reader, lock the resource
        }
        readers++;
        V(&rw_mutex);

        // Reading from the resource

        P(&rw_mutex);
        readers--;
        if (readers == 0) {
            V(&mutex); // If there are no more readers, unlock the resource
        }
        V(&rw_mutex);

        // Reading completed
    }
    return NULL;
}

void writer(void) {
    while (1) {
        P(&mutex); // Wait for the resource to be available
        // Writing to the resource
        V(&mutex); // Release the resource
    }
    return NULL;
}
```

#### 12.21
```c
#include "csapp.h"

#define N some_num // Maximum number of readers and writers

int readers = 0;
sem_t write_mutex, mutex;

void reader(void) {
    while (1) {
        P(&mutex);
        readers++;
        if (readers == 1) { /* First in */
            P(&write_mutex);
        }
        V(&mutex);

        /* Critical section */
		/* Reading happens  */

        P(&mutex);
        readers--;
        if (readers == 0) { /* Last out */
            V(&write_mutex);
        }
        V(&mutex);
    }
}

void writer(void) {
    while (1) {
        P(&write_mutex);
        /* Critical section */
        /* Writing happens  */
        V(&write_mutex);
    }
}
```

#### 12.22
```c
/* $begin select */
#include "csapp.h"
void echo_line(int connfd);
void command(void);

int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    fd_set read_set, ready_set;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    listenfd = Open_listenfd(argv[1]);

    FD_ZERO(&read_set);
    FD_SET(STDIN_FILENO, &read_set);
    FD_SET(listenfd, &read_set);

    int echo_ready = 0;

    while (1) {
        ready_set = read_set;
        Select(listenfd + 1, &ready_set, NULL, NULL, NULL);

        if (FD_ISSET(STDIN_FILENO, &ready_set))
            command(); /* Read command line from stdin */
        if (FD_ISSET(listenfd, &ready_set)) {
            clientlen = sizeof(struct sockaddr_storage);
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

            if (!echo_ready) {
                echo_line(connfd); /* Echo one line of client input */
                echo_ready = 1;
            }

            Close(connfd);
        }
    }
}

void command(void) {
    char buf[MAXLINE];
    if (!Fgets(buf, MAXLINE, stdin))
        exit(0); /* EOF */
    printf("%s", buf); /* Process the input command */
}

void echo_line(int connfd) {
    char buf[MAXLINE];
    if (Rio_readlineb(&connfd, buf, MAXLINE) > 0) {
        printf("Echoing: %s", buf);
        Rio_writen(connfd, buf, strlen(buf));
    }
}
/* $end select */
```

#### 12.23
The problem with the given event-driven concurrent echo server is that it relies on the `Rio_readlineb` function to read complete lines from the client. If a malicious client sends only a partial text line and never completes it, the server will block indefinitely waiting for the remaining data to arrive.

To improve the server so that it can handle partial text lines without blocking, we can modify the `check_clients` function to read data from the clients in a non-blocking way using `rio_readnb`.

```c
void check_clients(pool *p)
{
    int i, connfd, n;
    char buf[MAXLINE];
    rio_t rio;

    for (i = 0; (i <= p->maxi) && (p->nready > 0); i++) {
        connfd = p->clientfd[i];
        rio = p->clientrio[i];

        /* If the descriptor is ready, echo a text line from it */
        if ((connfd > 0) && (FD_ISSET(connfd, &p->ready_set)) && (p->nready > 0)) {
            p->nready--;

            if ((n = Rio_readnb(&rio, buf, MAXLINE)) != 0) {
                byte_cnt += n;
                printf("Server received %d (%d total) bytes on fd %d\n", n, byte_cnt, connfd);
                Rio_writen(connfd, buf, n);
            }
            /* EOF detected, remove descriptor from pool */
            else {
                Close(connfd);
                FD_CLR(connfd, &p->read_set);
                p->clientfd[i] = -1;
            }
        }
    }
}
```

#### 12.24
The Rio I/O package is designed to be thread-safe, but it may not be reentrant by default. Thread-safe means that the functions can be safely called concurrently by multiple threads without causing data corruption or unexpected behavior. However, reentrant functions go a step further and can be safely interrupted and called by multiple threads, even if they use shared data structures.

#### 12.25
The `echo_cnt` function, is thread-safe but not reentrant. Here's why:

**Thread-Safe:**
- `echo_cnt` is thread-safe because it uses a mutex (`sem_t mutex`) to protect the `byte_cnt` variable, ensuring that only one thread can access and modify it at a time.

**Not Reentrant:**
- `echo_cnt` is not reentrant because it uses global or static variables (`byte_cnt` and `sem_t mutex`) to maintain state. Reentrant functions should not rely on global or static variables, as they can lead to unexpected behavior if the function is interrupted and re-entered while it's in the middle of processing.

#### 12.26
```c
#include "csapp.h"

static sem_t mutex;

// Thread-safe gethostbyname
struct hostent *gethostbyname_ts(const char *hostname) {
    struct hostent *result = NULL;

    // Acquire the mutex to protect the shared data
    P(&mutex);

    struct hostent *original = gethostbyname(hostname);
    if (original != NULL) {
        // Perform a deep copy of the original hostent structure
        result = (struct hostent *)Malloc(sizeof(struct hostent));
        result->h_name = Strdup(original->h_name);
        result->h_aliases = Malloc(sizeof(char *) * 2); // At most 2 aliases
        result->h_aliases[0] = Strdup(original->h_aliases[0]);
        result->h_aliases[1] = NULL;
        result->h_addrtype = original->h_addrtype;
        result->h_length = original->h_length;
        result->h_addr_list = Malloc(sizeof(char *) * 2); // At most 2 addresses
        result->h_addr_list[0] = Malloc(original->h_length);
        memcpy(result->h_addr_list[0], original->h_addr_list[0], original->h_length);
        result->h_addr_list[1] = NULL;
    }

    // Release the mutex
    V(&mutex);

    return result;
}

int main(int argc, char **argv) {
    Sem_init(&mutex, 0, 1); // Initialize the mutex

    struct hostent *host = gethostbyname_ts(argv[1]);
    if (host != NULL) {
        printf("Official name: %s\n", host->h_name);
        printf("Aliases:\n");
        for (char **alias = host->h_aliases; *alias != NULL; alias++)
            printf("  %s\n", *alias);
    } else {
        herror("gethostbyname");
    }

    return 0;
}
```

#### 12.27
The issue arises from the fact that the `fdopen` function creates buffered I/O streams for the given file descriptor, and these buffered streams are not thread-safe by default.

1. Thread Interleaving: In a concurrent server, multiple threads are running concurrently and handling different client connections. Each thread might attempt to create its own `fpin` and `fpout` streams for a specific client socket.

2. Buffered I/O: Buffered I/O streams read or write data in chunks rather than individual characters. This buffering can lead to issues when multiple threads are using the same streams simultaneously. For example, one thread might read data while another thread is writing, and this can result in data being read or written out of order.

3. Lack of Synchronization: The `fdopen` function does not provide any synchronization mechanisms. This means that threads do not have any built-in protection against concurrent access to the same streams.

4. Closing Streams: When a thread finishes interacting with a client and calls `fclose` on `fpin` and `fpout`, it may inadvertently close streams that another thread is still using for another client.

#### 12.28
for i in case_1..=case_4 {
    println!("No effect!");
}

##### Case 1

<img alt="Progress Graph for Case 1" src="progress_graph_1.svg">

##### Case 2

<img alt="Progress Graph for Case 2" src="progress_graph_2.svg">

##### Case 3

<img alt="Progress Graph for Case 3" src="progress_graph_3.svg">

##### Case 4

<img alt="Progress Graph for Case 4" src="progress_graph_4.svg">

#### 12.29
From the following progress graph, we can see there is no way for this program to enter a deadlock state.

<img alt="Progress Graph for 12.29" src="progress_graph_5.svg">

#### 12.30
A.\
Thread 1: a & b, a & c

Thread 2: b & c

Thread 3: a & b

B.\
If a < b < c (meaning, a is acquired before b and b is acquired before c), we can see that:

- Thread 1 follows the order a -> b -> c.
- Thread 2 follows the order c -> b -> a.
- Thread 3 follows the order c -> b -> a.

Thread 2 and 3 violate the mutex lock ordering rule.

C.
| P(a);     |
| --------- |
| **P(b);** |
| **P(c);** |
| **V(c);** |
| **V(b);** |
| **V(a);** |

#### 12.31
```cmd
$ gcc tfgets-proc.c csapp.c -o tfgets -lpthread
```
See `tfgets-proc.c` for details.

#### 12.32
```cmd
$ gcc tfgets-select.c csapp.c -o tfgets -lpthread
```
See `tfgets-select.c` for details.

#### 12.33
```cmd
$ gcc tfgets-thread.c csapp.c -o tfgets -lpthread
```
See `tfgets-thread.c` for details.

#### 12.34
```cmd
$ gcc matrix-mul.c -o matrix -lpthread
Sequential Execution Time: 3.157496 seconds
Parallel Execution Time: 0.000002 seconds
```
See `matrix-mul.c` for details.

#### 12.35
```cmd
$ gcc tiny-proc.c csapp.c -o tiny-proc -lpthread
$ ./tiny-proc 8080
```
See `tiny-proc.c` for details.

#### 12.36
```cmd
$ gcc tiny-multiplex.c csapp.c -o tiny-mul -lpthread
$ ./tiny-mul 8080
```
See `tiny-multiplex.c` for details.

#### 12.37
```cmd
$ gcc tiny-thread.c csapp.c -o tiny-thread -lpthread
$ ./tiny-thread 8080
```
See `tiny-thread.c` for details.

#### 12.38
```cmd
$ gcc tiny-pthread.c csapp.c -o tiny-pthread -lpthread
$ ./tiny-pthread 8080
```
See `tiny-pthread.c` for details.

#### 12.39
See the proxy lab material for more information.
