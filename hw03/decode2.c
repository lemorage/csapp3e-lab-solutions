#include <stdio.h>

/**
 * gcc generates the following assembly code:
 * 1 decode2:
 * 2    subq        %rdx, %rsi      # y = y - z
 * 3    imulq       %rsi, %rdi      # x *= y
 * 4    movq        %rsi, %rax      # ret = y
 * 5    salq        $63, %rax       # ret << 63
 * 6    sarq        $63, %rax       # ret >> 63
 * 7    xorq        %rdi, %rax      # ret ^= x
 * 8    ret
 * Parameters x, y, and z are passed in registers %rdi, %rsi, and %rdx.
 * The code stores the return value in register %rax.
 * 
 */
long decode2(long x, long y, long z)
{
    // Subtraction: subq %rdx, %rsi
    y = y - z;

    // Multiplication: imulq %rsi, %rdi
    x = x * y;

    // Store y in %rax: movq %rsi, %rax
    long result = y;

    // Shift left: salq $63, %rax
    result = result << 63;

    // Shift right: sarq $63, %rax
    result = result >> 63;

    // XOR: xorq %rdi, %rax
    result = result ^ x;

    // Return the final result stored in %rax
    return result;
}