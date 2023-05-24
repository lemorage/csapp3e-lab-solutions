#include <stdio.h>
#include <assert.h>

/*
 * Mask with least significant n bits set to 1
 * Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
 * Assume 1 <= n <= w
 */
int lower_one_mask(int n)
{
    /* create a mask with n least significant bits set to 1
    by left shifting 1 by n and then subtracting 1. */
    int mask = (1 << (n - 1));
    return (mask << 1) - 1;
}

int main()
{
    assert(lower_one_mask(6) == 0x3F);
    assert(lower_one_mask(17) == 0x1FFFF);
    assert(lower_one_mask(32) == 0xFFFFFFFF);
    printf("All tests for lower-one-mask passed!\n");

    return 0;
}