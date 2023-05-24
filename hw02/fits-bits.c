#include <stdio.h>
#include <assert.h>

/*
 * Return 1 when x can be represented as an n-bit,
 * 2’s-complement number; 0 otherwise.
 * Assume 1 <= n <= w.
 */
int fits_bits(int x, int n)
{
    int w = sizeof(int) * 8;
    int shift = w - n;
    return (x << shift >> shift) == x;
}

int fits_bits_2(int x, int n)
{
    int minv = -(1 << (n - 1));
    int maxv = (1 << (n - 1)) - 1;
    return x >= minv && x <= maxv;
}

int main()
{
    assert(fits_bits(10, 5));
    assert(fits_bits(-10, 5));
    assert(fits_bits(255, 9));
    assert(fits_bits(-128, 8));
    assert(!fits_bits(128, 8));

    assert(fits_bits_2(10, 5));
    assert(fits_bits_2(-10, 5));
    assert(fits_bits_2(255, 9));
    assert(fits_bits_2(-128, 8));
    assert(!fits_bits_2(128, 8));
    printf("All tests for fits-bits passed!\n");

    return 0;
}