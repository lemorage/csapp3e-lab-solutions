#include <limits.h>

int threefourths(int x) {
    int is_negative = x & INT_MIN;   // Check if x is negative
    int bias = (1 << 2) - 1;         // Compute the bias value (3 - 1)
    int sign_correction = is_negative ? bias : 0;
    int shift_amount = 2;            // Compute the shift amount
    int shifted = x >> shift_amount; // Perform the right shift
    int rounding_correction = (shifted & 3) == 3 ? 1 : 0;
    int result = (shifted + sign_correction + rounding_correction) >> 2;  // Perform the division
    return result;
}

int main()
{
    return 0;
}
