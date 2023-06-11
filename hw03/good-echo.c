#include <stdio.h>

void good_echo()
{
    char buffer[BUFSIZ];  // Buffer to hold the input line

    // Read input line using fgets
    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        // Write the input line to standard output
        if (fputs(buffer, stdout) == EOF)
        {
            // Error occurred while writing
            fprintf(stderr, "Error writing to standard output.\n");
            return;
        }
    }
    else
    {
        // Error occurred while reading
        fprintf(stderr, "Error reading from standard input.\n");
        return;
    }
}
