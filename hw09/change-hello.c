#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd;
    char *data;
    struct stat sbuf;

    // Open the file for read/write
    if ((fd = open("hello.txt", O_RDWR)) == -1) {
        perror("open");
        exit(1);
    }

    // Get the size of the file
    if (stat("hello.txt", &sbuf) == -1) {
        perror("stat");
        exit(1);
    }

    // Map the file to memory
    if ((data = mmap((caddr_t)0, sbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == (caddr_t)(-1)) {
        perror("mmap");
        exit(1);
    }

    // Change "Hello" to "Jello"
    data[0] = 'J';

    // Cleanup
    if (munmap(data, sbuf.st_size) == -1) {
        perror("munmap");
        exit(1);
    }

    close(fd);
    return 0;
}
