#include <stdio.h>

int main()
{
    unsigned int x = 0x89ABCDEF;
    unsigned int y = 0x76543210;
    
    // Mask the least significant byte of x
    unsigned int masked_x = x & 0xFF;

    // Mask off the least significant byte of y
    unsigned int marked_y = y & 0xFFFFFF00;

    // Combine the masked_x and marked_y to get the desired word
    unsigned int result = masked_x | marked_y;

    printf("%x\n", result);

    return 0;
}