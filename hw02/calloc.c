#include <stdlib.h>
#include <string.h>

void *calloc(size_t nmemb, size_t size) {
    // Check for zero arguments
    if (nmemb == 0 || size == 0) {
        return NULL;
    }

    // Calculate the total size to be allocated
    size_t total_size = nmemb * size;

    // Check for potential overflow
    if (nmemb != 0 && total_size / nmemb != size) {
        return NULL;
    }

    // Allocate memory using malloc
    void *ptr = malloc(total_size);

    if (ptr != NULL) {
        // Set the allocated memory to zero using memset
        memset(ptr, 0, total_size);
    }

    return ptr;
}

int main()
{
    return 0;
}