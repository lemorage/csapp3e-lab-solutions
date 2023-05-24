#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b)
{
     // Calculate the shift value based on the byte index i
    int shift = i * 8;

    // Clear the byte at index i
    x &= ~(0xFF << shift);

    // Set the byte at index i to the new value b
    x |= (b << shift);

    return x;
}

int main()
{
    printf("%x\n", replace_byte(0x12345678, 2, 0xAB)); // 0x12AB5678
    printf("%x\n", replace_byte(0x12345678, 0, 0xAB)); // 0x123456AB

    return 0;
}