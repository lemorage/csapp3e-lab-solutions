#include <string.h>

/**
 * A. The conditional test in the code always succeeds because
 * the expression maxbytes-sizeof(val) >= 0 compares an unsigned value
 * (the result of sizeof(val)) with a signed value (maxbytes).
 * When an unsigned value is compared with a signed value, the signed value
 * is implicitly converted to an unsigned value, resulting in unexpected behavior.
 * 
 * In this case, if maxbytes is smaller than sizeof(val), the subtraction
 * maxbytes-sizeof(val) will underflow and wrap around, resulting in a large positive value.
 * As a result, the condition maxbytes-sizeof(val) >= 0 will always be true.
 * 
 * B. By explicitly casting sizeof(val) to int, we ensure the comparison is done correctly.
 */
void copy_int(int val, void *buf, int maxbytes) {
    if (maxbytes >= (int)sizeof(val))
        memcpy(buf, (void *)&val, sizeof(val));
}

int main()
{
    return 0;
}
