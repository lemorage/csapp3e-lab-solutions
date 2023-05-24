#include <limits.h>

int mul3div4(int x) {
    int mul = (x << 1) + x;         // Compute 3 * x
    int is_negative = mul & INT_MIN;  // Check if the result is negative
    int correction = (1 << 2) - 1;   // Compute the correction value (3 - 1)
    int bias = is_negative ? correction : 0;
    int result = (mul + bias) >> 2;  // Perform the division
    return result;
}

int main()
{
    return 0;
}
