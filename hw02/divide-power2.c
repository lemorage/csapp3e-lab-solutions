#include <limits.h>

int divide_power2(int x, int k) {
    int is_negative = x & INT_MIN;  // Check if x is negative
    int bias = (1 << k) - 1;        // Compute the bias value
    int correction = is_negative ? bias : 0;
    int result = (x + correction) >> k;  // Perform the division
    return result;
}

int main()
{
    return 0;
}
