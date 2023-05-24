#include <stdio.h>
#include <assert.h>

unsigned srl(unsigned x, int k) 
{
    unsigned xsra = (int) x >> k;
    unsigned mask = ~(~0 << (8 * sizeof(int) - k)); // create a mask of k bits
    return xsra & mask; // apply the mask to xsra to perform logical right shift
}

int sra(int x, int k)
{
    int xsrl = (unsigned) x >> k;
    int sign = (x & 1 << (8 * sizeof(int) - 1)); // get the sign bit of x
    int mask = ~(sign - 1); // create a mask of all 1s if sign bit is 1, 0 otherwise
    return xsrl | (mask << (8 * sizeof(int) - k)); // apply the mask to xsrl to perform arithmetic right shift
}

int main()
{
    // test srl()
    assert(srl(0b11100000, 3) == 0b00011100);
    assert(srl(0b10101010, 4) == 0b00001010);
    assert(srl(0b00001111, 2) == 0b00000011);

    // test sra()
    assert(sra(0b11100000, 3) == (0b11111100 & 0b00011100));
    assert(sra(0b10101010, 4) == (0b11111010 & 0b00001010));
    assert(sra(0b00001111, 2) == 0b00000011);

    printf("All tests for srl-sra passed!\n");
    return 0;
}