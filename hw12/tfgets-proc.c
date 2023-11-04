#include "csapp.h"

char *tfgets(char *s, int size, FILE *stream, int timeout);

sigjmp_buf env;

void sigalarm_handler(int signum) {
    // Handle the timeout
    siglongjmp(env, 1);
}

int main() {
    char buf[MAXLINE];

    if (tfgets(buf, MAXLINE, stdin, 5) == NULL)
        printf("BOOM!\n");
    else
        printf("%s", buf);

    exit(0);
}

char *tfgets(char *s, int size, FILE *stream, int timeout) {
    pid_t childpid;
    int pipefd[2];

    if (pipe(pipefd) < 0)
        unix_error("pipe error");

    if ((childpid = Fork()) == 0) {
        // This is the child process

        Close(pipefd[0]);
        Signal(SIGALRM, sigalarm_handler);

        // Set a timeout using setjmp and longjmp
        if (sigsetjmp(env, 1) == 0) {
            alarm(timeout);
            char *result = fgets(s, size, stream);
            if (result == NULL)
                exit(1);
            Write(pipefd[1], result, strlen(result));
        }

        exit(0);
    } else {
        // This is the parent process

        Close(pipefd[1]);
        char buf[MAXLINE];

        int n = Read(pipefd[0], buf, MAXLINE);

        if (n > 0) {
            buf[n] = '\0';
            Close(pipefd[0]);
            return printf("%s", strdup(buf)), strdup(buf);
        } else {
            Close(pipefd[0]);
            return NULL;
        }
    }
}
