#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>

char *tfgets(char *s, int size, FILE *stream) {
    fd_set readfds;
    struct timeval timeout;

    // Set up the file descriptor set.
    FD_ZERO(&readfds);
    FD_SET(fileno(stream), &readfds);

    // Set up the timeout. 5 seconds.
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    // Wait until input arrives on stdin (fd 0) or until we timeout.
    int retval = select(fileno(stream) + 1, &readfds, NULL, NULL, &timeout);
    if (retval == -1) {
        perror("select");
        return NULL;
    } else if (retval > 0) {
        // Data is available, call fgets to read it.
        return fgets(s, size, stream);
    } else {
        // Timeout occurred.
        return NULL;
    }
}

int main(void) {
    char buffer[256];
    printf("You have 5 seconds to enter a line of text...\n");
    if (tfgets(buffer, sizeof(buffer), stdin) != NULL) {
        printf("You entered: %s", buffer);
    } else {
        printf("Timeout occurred.\n");
    }
    return 0;
}