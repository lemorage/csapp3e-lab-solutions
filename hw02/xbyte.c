typedef unsigned packed_t;
/**
 * A. The code provided in the "Failed attempt at xbyte" has the following issues:
 * 
 * 1. The code only performs a right shift (`>>`) on the `word` by `(bytenum << 3)` bits,
 * which effectively moves the desired byte to the least significant byte position.
 * However, it does not handle sign extension, which is necessary to convert
 * the extracted byte to a 32-bit signed integer.
 * 
 * 2. The code applies a bitwise AND operation (`&`) with `0xFF` to mask out
 * the lower 8 bits and discard any potential sign extension that might have occurred
 * during the right shift. This results in the extracted byte being treated as an unsigned value,
 * rather than a sign-extended 32-bit signed integer.
 * 
 * B. Here's a correct implementation of the `xbyte` function using left and right shifts, along with one subtraction:
 * 
 * 1. We calculate the number of bits to shift by multiplying `bytenum` by 8 (`(bytenum << 3)`),
 * which gives the bit position of the desired byte.
 * 
 * 2. Instead of directly right-shifting the `word`, we left-shift it by `(32 - 8 - shift)` bits.
 * This effectively moves the desired byte to the most significant byte position, while preserving the sign bit.
 * 
 * 3. Then, we perform an arithmetic right shift on the left-shifted value by 24 bits (`>> 24`).
 * This shift propagates the sign bit to the right, resulting in the sign extension of the extracted byte.
 * 
 * 4. Finally, we return the sign-extended value as the result.
 */
int xbyte(packed_t word, int bytenum) {
    int shift = (bytenum << 3);  // Calculate the number of bits to shift

    // Perform an arithmetic right shift to propagate the sign bit
    int result = (int)(word << (32 - 8 - shift)) >> 24;

    return result;
}

int main()
{
    return 0;
}
