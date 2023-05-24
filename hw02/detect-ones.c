#include <stdio.h>
#include <assert.h>

/* Return 1 when any odd bit of x equals 1; 0 otherwise.
    Assume w=32 */
int any_odd_one(unsigned x);

/* Return 1 when x contains an odd number of 1s; 0 otherwise.
   Assume w=32 */
int odd_ones(unsigned x);

/*
 * Generate mask indicating leftmost 1 in x.  Assume w=32.
 * For example, 0xFF00 -> 0x8000, and 0x6600 --> 0x4000.
 * If x = 0, then return 0.
 */
int leftmost_one(unsigned x);

int any_odd_one(unsigned x)
{
    /* The mask 0xAAAAAAAA has all odd bits set to 1 */
    int mask = 0xAAAAAAAA;
    /* Return 1 if there's any bit in x that's 1 in the odd bit positions */
    return !!(x & mask);
}

/* For demonstrating purpose, this is the looping way. */
unsigned int count_ones(unsigned int x)
{
    unsigned int count = 0;
    for (int i = 0; i < 32; i++)
        count += (x >> i) & 1;
    return count;
}

int odd_ones(unsigned x)
{
    /* Pairwise cancellation to count number of 1 bits */
    x ^= x >> 16; /* XOR upper and lower 16 bits */
    x ^= x >> 8;  /* XOR upper and lower 8 bits */
    x ^= x >> 4;  /* XOR upper and lower 4 bits */
    x ^= x >> 2;  /* XOR upper and lower 2 bits */
    x ^= x >> 1;  /* XOR upper and lower 1 bit */

    /* Test if number of 1 bits is odd */
    return x & 1; /* Check if lowest bit is set */
}

int leftmost_one(unsigned x)
{
    /* Set all bits to the right of the leftmost 1 to 1 */
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    
    /* Set all bits to the right of the leftmost 1 to 0 */
    return x & ~(x >> 1);
}

/* For demonstrating purpose, this is the looping way. */
unsigned int set_right_bits(unsigned int x)
{
    for (int i = 1; i < 32; i *= 2)
        x |= (x >> i);
    return x;
}

int main()
{
    assert(any_odd_one(0xAAAAAAAA));
    assert(!any_odd_one(0x55555555));

    assert(!odd_ones(0xAAAAAAAA));
    assert(!odd_ones(0x55555555));

    assert(leftmost_one(0xFF00) == 0x8000);
    assert(leftmost_one(0x6600) == 0x4000);
    assert(!leftmost_one(0x0));
}