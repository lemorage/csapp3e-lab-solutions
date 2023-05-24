#include <stdio.h>

/* A. The code fails to comply with the C standard
because it performs a left shift by a value greater than
or equal to the width of the type of the left operand,
which is undefined behavior according to the C standard.
In this case, the left operand is an int type and its width
is 32 bits, but the code attempts to shift it by 32 bits,
which is not allowed by the standard. */


/* B. This modified code uses the fact that shifting a bit
left by 1 position is equivalent to multiplying it by 2.
By shifting set_msb left by 1 position, we get a value
that is beyond the most significant bit of a 32-bit integer.
If int is at least 32 bits, this value will be greater than 0.
If int is less than 32 bits, this value will be equal to 0. */
int int_size_is_32()
{
    int set_msb = 1 << 31;
    int beyond_msb = set_msb << 1;
    return set_msb && !beyond_msb;
}


int int_size_is_16()
{
    int set_msb = 1 << 15 << 15 << 1;
    int beyond_msb = set_msb << 1;
    return set_msb && !beyond_msb;
}

int main()
{
    return 0;
}