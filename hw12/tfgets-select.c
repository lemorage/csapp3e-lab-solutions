#include "csapp.h"

char *tfgets(char *s, int size, int timeout);

int main() {
    char buf[MAXLINE];

    if (tfgets(buf, MAXLINE, 5) == NULL)
        printf("BOOM!\n");
    else
        printf("%s", buf);

    exit(0);
}

char *tfgets(char *s, int size, int timeout) {
    fd_set fds;
    struct timeval tv;

    int fd = 0;  // Standard input

    FD_ZERO(&fds);
    FD_SET(fd, &fds);

    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    int result = select(fd + 1, &fds, NULL, NULL, &tv);

    if (result == -1) {
        if (errno == EINTR)
            fprintf(stderr, "tfgets: Timed out\n");
        return NULL;
    }

    if (result == 1)
        return Fgets(s, size, stdin);

    return NULL;
}
