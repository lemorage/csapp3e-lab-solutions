/* 
 * CS:APP Data Lab 
 * 
 * name: Glenn Miao | userid: lemorage
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /* exploit ability of De Morgan's laws to achieve the functionality of bitwise XOR */
  int a = ~(x & y);
  int b = ~(~x & ~y);
  int result = a & b;
  return result;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /* exploit ability of shifts to compute tmin */
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 2
 */
int isTmax(int x) {
  /* exploit relationship of Tmin and Tmax to detect Tmax */
  /* Tmax is a number where all bits are 1 except the sign bit. */
  
  /* First, check if x + 1 is equal to -(2^31), which is Tmin.
     If it is, then x is Tmax. 
     Therefore, sum = x + 1 and neg = ~x should be equal.
     But we are also checking that x is not Tmin since Tmin
     is its own additive inverse.
     We use the double negation to check that neg is not 0. */
  int sum = x + 1;
  int neg = ~x;
  return !((sum ^ neg) | !neg); // !(sum ^ neg) & !!neg
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /* create a mask with every other bit set to 1 */
  int mask = (0xAA | (0xAA << 8));
  /* shift the mask to cover all odd-numbered bits */
  mask = mask | (mask << 16);
  /* check if all odd-numbered bits in x are set to 1 */
  return !((x & mask) ^ mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /* exploit ability of (~x + 1) to compute the -x */
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  // Initialize variables for sign bit and limits
  int signBit = 1 << 31;

  int upperLimit = ~(signBit | 0x39);
  
  int lowerLimit = ~0x30;

  // Check if x is less than upper limit
  int lessThanUpper = signBit & ((upperLimit + x) >> 31);

  // Check if x is greater than lower limit
  int greaterThanLower = signBit & ((lowerLimit + 1 + x) >> 31);

  // Return 1 if x is within the range of [0x30, 0x39]
  return !(lessThanUpper | greaterThanLower);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /* create a mask that will be either all ones (if x is non-zero)
     or all zeros (if x is zero) */
  int mask = ~(!!x) + 1;
  /* use the mask and bitwise AND to select between y and z */
  int result = (mask & y) | (~mask & z);
  return result;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int sign_x = (x >> 31) & 1;
  int sign_y = (y >> 31) & 1;

  // If the signs are different, then x is less than y if x is negative
  int diff_sign = sign_x ^ sign_y; // 0
  int neg_x = sign_x & 1;
  int less_if_diff_sign = (diff_sign & neg_x);

  // If the signs are the same, then x is less than y if y - x is non-negative
  int same_sign = !diff_sign;
  int diff = y + (~x + 1); // y - x
  int non_neg_diff_xy = ~(diff >> 31);

  return less_if_diff_sign | (same_sign & non_neg_diff_xy);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  // if x is 0, then ~x is also 0.
  // if x is nonzero, then x | ~x must be -1 (Sign Extension)
  int negX = ~x + 1;  // negate x
  int sign = (x | negX) >> 31; // get the sign bit of x or -x

  return sign + 1; // return 1 if x is 0, otherwise 0
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  /* exploit ability of binary search to count the bits */

  int sign = x >> 31;  // extract sign bit  
  int bitCount = 0, check;

  // x = (x ^ sign) + (~sign + 1);
  x = (~x & sign) | (~sign & x);  // get absolute value of x

  bitCount += !!(x >> 16) << 4;  // check upper 16 bits
  x >>= bitCount;

  bitCount += (check = !!(x >> 8) << 3);  // check next 8 bits
  x >>= check;
  
  bitCount += (check = !!(x >> 4) << 2);  // check next 4 bits
  x >>= check;

  bitCount += (check = !!(x >> 2) << 1);  // check next 2 bits
  x >>= check;

  bitCount += (check = !!(x >> 1));  // check last bit
  x >>= check;

  return bitCount + x + 1; // account for sign bit

  /* A cheating way of ...

  int sign = x >> 31;  // sign bit
  x = (sign & ~x) | (~sign & x);  // if x is negative, get its two's complement
  int numBits = 0;

  numBits = (!!x) + (!!((x >> 1) & 0x7FFFFFFF)) + (!!((x >> 2) & 0x3FFFFFFF)) + (!!((x >> 3) & 0x1FFFFFFF)) +
            (!!((x >> 4) & 0x0FFFFFFF)) + (!!((x >> 5) & 0x07FFFFFF)) + (!!((x >> 6) & 0x03FFFFFF)) + 
            (!!((x >> 7) & 0x01FFFFFF)) + (!!((x >> 8) & 0x00FFFFFF)) + (!!((x >> 9) & 0x007FFFFF)) +
            (!!((x >> 10) & 0x003FFFFF)) + (!!((x >> 11) & 0x001FFFFF)) + (!!((x >> 12) & 0x000FFFFF)) + 
            (!!((x >> 13) & 0x0007FFFF)) + (!!((x >> 14) & 0x0003FFFF)) + (!!((x >> 15) & 0x0001FFFF)) + 
            (!!((x >> 16) & 0x0000FFFF)) + (!!((x >> 17) & 0x00007FFF)) + (!!((x >> 18) & 0x00003FFF)) + 
            (!!((x >> 19) & 0x00001FFF)) + (!!((x >> 20) & 0x00000FFF)) + (!!((x >> 21) & 0x000007FF)) + 
            (!!((x >> 22) & 0x000003FF)) + (!!((x >> 23) & 0x000001FF)) + (!!((x >> 24) & 0x000000FF)) + 
            (!!((x >> 25) & 0x0000007F)) + (!!((x >> 26) & 0x0000003F)) + (!!((x >> 27) & 0x0000001F)) + 
            (!!((x >> 28) & 0x0000000F)) + (!!((x >> 29) & 0x00000007)) + (!!((x >> 30) & 0x00000003)) + 
            (!!((x >> 31) & 0x00000001));
  
  return numBits + 1;
  
  */
}
//float
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  unsigned sign = uf & (1 << 31); // get the sign bit
  unsigned exponent = uf & 0x7F800000; // get the exponent field
  unsigned mantissa = uf & 0x007FFFFF; // get the fraction field

  if (exponent == 0x7F800000)
    return uf;  // NaN or infinity

  if (!exponent)
    mantissa <<= 1;  // denormalized number or zero
  else
    if ((exponent += 0x00800000) == 0x7F800000) // normalized number
      return sign | exponent;  // overflow to infinity

  return sign | exponent | mantissa;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  int neg = 1 << 31; // create a mask (0x80000000)
  int sign = x & neg; // extract the sign bit
  int exponent = 31; // initialize the exponent
  int bias = 127;
  int mantissa;
  
  if (!x) // if x is zero, return zero
    return x;
  if (x == neg) // if x is the TMin, return the its float representation
    return neg | ((exponent + bias) << 23);
  
  // get abs(x)
  x = sign ? ~x + 1 : x;
  while (!(x & neg)) // left shift x and count the number of shifts in exponent
    x <<= 1, --exponent;

  // extract the mantissa bits by shifting x right by 8 bits
  mantissa = (((~neg) & x) >> 8);
  if (x & 0x80 && ((mantissa & 1) || ((x & 0x7f)))) // perform rounding if necessary
    ++mantissa;

  return sign + ((exponent + bias) << 23) + mantissa;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  // extract the sign, exponent, and fraction/mantissa from uf
  unsigned sign = uf >> 31;
  unsigned exponent = (uf >> 23) & 0xFF;
  unsigned mantissa = uf & 0x7FFFFF;
  int bias = 0x7F;
  int result;

  // handle special cases: NaN, infinity, and denormalized numbers
  if (exponent == 0xFF)
    return 0x80000000u;
  if (exponent < bias)
    return 0;

  // add the implicit leading 1 for normalized numbers
  // mantissa = exponent ? mantissa | 0x80000000 : mantissa | 0x800000;

  // adjust the exponent bias
  exponent -= bias;

  // shift the fraction based on the exponent
  if (exponent >= 31)
    return 0x80000000u;  // out of range
  
  result = ((exponent > 22) ? mantissa << (exponent - 23) : mantissa >> (23 - exponent)) + (1 << exponent);

  // Apply the sign
  return sign ? -result : result; // (result ^ sign) - sign;
}
