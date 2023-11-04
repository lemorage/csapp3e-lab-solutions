#include "csapp.h"

char *tfgets(char *s, int size, int timeout);

static void *tfgets_thread(void *arg);

int main() {
    char buf[MAXLINE];

    if (tfgets(buf, MAXLINE, 5) == NULL)
        printf("BOOM!\n");
    else
        printf("%s", buf);

    exit(0);
}

char *tfgets(char *s, int size, int timeout) {
    pthread_t tid;
    void *result;
    struct timeval tv;

    int *args = malloc(2 * sizeof(int));
    args[0] = size;
    args[1] = timeout;

    Pthread_create(&tid, NULL, tfgets_thread, args);

    Pthread_join(tid, &result);

    free(args);

    return (char *)result;
}

static void *tfgets_thread(void *arg) {
    int *args = (int *)arg;
    int size = args[0];
    int timeout = args[1];

    char *s = malloc(size);
    fd_set fds;
    struct timeval tv;

    int fd = 0; // Standard input

    FD_ZERO(&fds);
    FD_SET(fd, &fds);

    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    int result = select(fd + 1, &fds, NULL, NULL, &tv);

    if (result == -1) {
        if (errno == EINTR)
            fprintf(stderr, "tfgets: Timed out\n");
        free(s);
        return NULL;
    }

    if (result == 1) {
        s = Fgets(s, size, stdin);
        return printf("%s", s), s;
    }

    return NULL;
}
