#include <stdio.h>

int main()
{
    int x = 0b11111111; // Binary representation of 255

    // Test expression A
    if ((x & (~0)) != 0)
        printf("A. Any bit of x equals 1: True\n");
    else
        printf("A. Any bit of x equals 1: False\n");

    // Test expression B
    if ((x & ~0) != ~0)
        printf("B. Any bit of x equals 0: True\n");
    else
        printf("B. Any bit of x equals 0: False\n");

    // Test expression C
    if ((x & 0xFF) != 0)
        printf("C. Any bit in the least significant byte of x equals 1: True\n");
    else
        printf("C. Any bit in the least significant byte of x equals 1: False\n");

    // Test expression D
    if (((unsigned)x >> (sizeof(int) - 1) * 8) != 0)
        printf("D. Any bit in the most significant byte of x equals 0: True\n");
    else
        printf("D. Any bit in the most significant byte of x equals 0: False\n");

    return 0;
}
