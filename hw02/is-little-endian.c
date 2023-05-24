#include <stdio.h>

int is_little_endian()
{
    short x = 0x0001;
    char *c = (char *) &x;
    return *c;
}

int main()
{
    if (is_little_endian())
        printf("This machine is little-endian.\n");
    else
        printf("This machine is big-endian.\n");
    
    return 0;
}