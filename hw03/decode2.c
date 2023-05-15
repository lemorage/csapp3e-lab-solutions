#include <stdio.h>

/**
 * gcc generates the following assembly code:
 * 1 decode2:
 * 2    subq        %rdx, %rsi
 * 3    imulq       %rsi, %rdi
 * 4    movq        %rsi, %rax
 * 5    salq        $63, %rax
 * 6    sarq        $63, %rax
 * 7    xorq        %rdi, %rax
 * 8    ret
 * Parameters x, y, and z are passed in registers %rdi, %rsi, and %rdx.
 * The code stores the return value in register %rax.
 * 
 */
long decode2(long x, long y, long z)
{

}