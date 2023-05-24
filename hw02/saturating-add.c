#include <limits.h>

int saturating_add(int x, int y) {
    int sum = x + y;
    
    // Check for overflow
    int overflow = ((x ^ sum) & (y ^ sum)) >> (sizeof(int) * CHAR_BIT - 1);
    
    // Calculate the saturated result
    int result = (sum & ~overflow) | (INT_MAX & overflow);
    
    return result;
}

int main()
{
    return 0;
}
