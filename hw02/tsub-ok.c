#include <limits.h>

/**
 * The tsub_ok function checks for overflow when subtracting y from x.
 * It performs the subtraction and then checks for two cases of overflow:
 *  - Positive Overflow: If x is non-negative, y is negative,
 *    and the result of the subtraction sub is negative,
 *    it means that there was an overflow in the positive range.
 *  - Negative Overflow: If x is negative, y is non-negative,
 *    and the result of the subtraction sub is non-negative,
 *    it means that there was an overflow in the negative range.
 * If either of these overflow cases is detected, the function returns 0, Otherwise, it returns 1.
 */
int tsub_ok(int x, int y) {
    int sub = x - y;
    int pos_overflow = x >= 0 && y < 0 && sub < 0;
    int neg_overflow = x < 0 && y >= 0 && sub >= 0;
    return !pos_overflow && !neg_overflow;
}

int main()
{
    return 0;
}
