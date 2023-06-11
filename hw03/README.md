> Extensions:\
>    `.64s`: x86-64 assembly code\
>    `.64bs`: x86-64 assembly code with conditional moves disabled\
>    `.O1-64s`: x86-64 assembly code compiled with -O1 optimization\

<br />
FILES

- 3.58 `decode2.c`
- 3.61 `cread-alt.c`
- 3.62 `switch3.c`
- 3.63 `switch-prob.c`
- 3.71 `good-echo.c`
- 3.74 `find-range.c`

<br/>
ANSWERS

#### 3.59
The algorithm used to compute the product of two 64-bit signed values `x` and `y` and store the result in memory is as follows:

1. Extend the 64-bit values `x` and `y` to 128 bits by rewriting them as:
   - `x = 2^64 * xh + xl`, where `xh` and `xl` are 64-bit values.
   - `y = 2^64 * yh + yl`, where `yh` and `yl` are 64-bit values.

2. Compute the 128-bit product `p` using the extended values:
   - `p = 2^64 * ph + pl`, where `ph` and `pl` are 64-bit values.

3. Store the values of `ph` and `pl` in memory.

<br/>

```assembly
1 store_prod:
2    movq     %rdx, %rax        ; Move value of y (yl) into %rax
3    cqto                       ; Sign-extend %rax into %rdx: %rdx:%rax = 64-bit yh:yl
4    movq     %rsi, %rcx        ; Move value of x (xl) into %rcx
5    sarq     $63, %rcx         ; Arithmetic right shift %rcx (xl) by 63 bits to obtain sign extension in %rcx
6    imulq    %rax, %rcx        ; Multiply %rax (yl) by %rcx (sign-extended xl) to get the partial product ph (low bits)
7    imulq    %rsi, %rdx        ; Multiply %rsi (xh) by %rdx (sign-extended yl) to get the partial product pl (high bits)
8    addq     %rdx, %rcx        ; Add the high bits (pl) to the low bits (ph) in %rcx to obtain the final value of ph
9    mulq     %rsi              ; Multiply %rsi (xh) by %rdi (yl) to get the high bits of the 128-bit product
10   addq     %rcx, %rdx        ; Add the low bits (ph) to the high bits (stored in %rdx) to obtain the final value of pl
11   movq     %rax, (%rdi)      ; Store the low 64 bits (pl) of the product in memory at address %rdi
12   movq     %rdx, 8(%rdi)     ; Store the high 64 bits (ph) of the product in memory at address %rdi + 8
13   ret                        ; Return from the function
```

The assembly code follows the algorithm described above. It uses multiplication instructions (`imulq`, `mulq`) to perform the partial products and addition instructions (`addq`) to combine the partial products to obtain the final product. The extended values of `x` and `y` are stored in registers `%rax`, `%rdx`, `%rcx`, and `%rsi`, and the final product is stored in memory at the provided address.

#### 3.60
```assembly
1   loop:
2       movl %esi, %ecx
3       movl $1, %edx
4       movl $0, %eax
5       jmp .L2
6   .L3:
7       movq %rdi, %r8
8       andq %rdx, %r8
9       orq  %r8, %rax
10      salq %cl, %rdx
11  .L2:
12      testq %rdx, %rdx
13      jne .L3
14      rep; ret
```
<br/>
A. The registers holding program values are as follows:
- `%rdi` holds the value of `x`
- `%esi` holds the value of `n`
- `%rax` holds the value of `result`
- `%rdx` holds the value of `mask`

B. The initial values of `result` and `mask` are as follows:
- `result` is initialized to `0` (`movl $0, %eax` sets `%eax` to `0`, and `%rax` inherits the value)
- `mask` is initialized to `1` (`movl $1, %edx` sets `%edx` to `1`, and `%rdx` inherits the value)

C. The test condition for `mask` is `mask != 0` (`testq %rdx, %rdx` tests if `%rdx` is not equal to `0`)

D. The `mask` gets updated by performing a left shift operation (`salq %cl, %rdx`) where `%cl` holds the value of `%ecx`, which in turn holds the value of `%esi`. The left shift operation shifts the bits in `%rdx` to the left by `%cl` positions.

E. The `result` gets updated by performing a bitwise OR operation (`orq %r8, %rax`) where `%r8` holds the value of `%rdi` (copy of `x`) AND-ed with `%rdx` (mask). The result is then OR-ed with `%rax`.

F. The completed C code:
```c
long loop(long x, long n)
{
    long result = 0;
    long mask;
    for (mask = 1; mask != 0; mask = mask << n) {
        result |= (x & mask);
    }
    return result;
}
```

#### 3.64
A. To extend Equation 3.1 for a three-dimensional array, `A[i][j][k]`, we need to consider the sizes of each dimension. Let's assume the size of the data type `T` is `L` bytes.

The formula for the memory address of `A[i][j][k]` can be derived as follows:

> &D[i][j][k] = x~D~ + L(C * (R * i + j) + k)

Here,
- `R` represents the size of the first dimension (number of rows)
- `C` represents the size of the second dimension (number of columns)
- `L` is the size of the data type `T` in bytes
- x~D~ represents the base address of the array `A`

B. Based on the assembly code, we can infer the values of `R`, `S`, and `T`:

- R: The value of R is represented by the shift and addition operations in the assembly code. From line 5 (`salq $6, %rsi`), we see that the value 6 is used to shift the value of `%rsi (j)` left by 6 bits. This indicates that R is equal to 2^6, which is 64.

- S: The value of S is represented by the multiplication operation in the assembly code. From line 6 (`addq %rsi, %rdi`), we see that the value of `%rsi (j)` is added to `%rdi (i)`. This addition operation indicates that S is equal to the value of the second dimension, which is R.

- T: The value of T is represented by the multiplication and addition operations in the assembly code. From line 7 (`addq %rax, %rdi`), we see that the value of `%rax (k)` is added to `%rdi (i+j*R)`. This addition operation indicates that T is equal to the value of the third dimension, which is S.

Therefore, based on the assembly code, we have R = 64, S = 64, and T = 64.

#### 3.65 
A. Based on the assembly code, the register that holds a pointer to array element `A[i][j]` is `%rax`.

B. Similarly, the register that holds a pointer to array element `A[j][i]` is `%rdx`.

C. The value of M can be determined from the assembly code. In line 8 `($120, %rax)`, the value 120 is loaded into the %rax register. Since `%rax` holds a pointer to array element `A[i][j]`, and the size of each element in the array is 8 bytes (as indicated by the`movq` instructions), we can calculate the value of `M` as 120 / 8, which is 15. Therefore, the value of `M` is 15.

#### 3.66
NR = 4 * (n + 1), NC = n * 3

#### 3.67
A. Diagram of the stack frame for eval:
```
High Address
-----------------
| Return Address |
-----------------
|   s.p (z)      |
-----------------
|   s.a[1] (y)   |
-----------------
|   s.a[0] (x)   |
-----------------
|   Local Vars   |
-----------------
Low Address
```
The stack frame for eval consists of the return address, followed by the arguments `x`, `y`, and `z`, and any local variables.

B. In its call to process, eval passes the structure `s` as the argument.

C. The code for process accesses the elements of the structure argument `s` using the register `%rdi` as the base address. For example, `%rdi` holds the address of `s`, and the code uses offset values to access specific elements of the structure, such as `s.a[0]`, `s.a[1]`, and `s.p`.

D. The code for process sets the fields of the result structure `r` using the register `%rdi` as the base address. It uses offset values to access and set specific elements of the structure, such as `r.u[0]`, `r.u[1]`, and `r.q`. The values are assigned to these elements using the `movq` instruction.

E. Completed diagram of the stack frame for eval after the return from process:
```
High Address
-----------------
| Return Address |
-----------------
|   s.p (z)      |
-----------------
|   s.a[1] (y)   |
-----------------
|   s.a[0] (x)   |
-----------------
|   r.u[1] (q)   |
-----------------
|   r.u[0]       |
-----------------
|   Local Vars   |
-----------------
Low Address
```
Following the return from process, the stack frame for eval includes the elements of the structure `r` that were returned by the process function.

F. From the given code and the generated assembly, we can discern the following principles about how structure values are passed as function arguments and returned as function results:
- Structure arguments are typically passed by copying the entire structure onto the stack or using registers to hold the structure's address and accessing its elements with offset values.
- Structure results are typically returned by copying the entire structure onto the stack or using registers to hold the structure's address and setting its elements with offset values.
- The offsets for accessing structure elements are determined based on the size and layout of the structure, typically using the size of the data types within the structure and their order of declaration.
- Stack frames are used to allocate memory for local variables, function arguments, and return values, with the stack pointer adjusted accordingly.

#### 3.68
Since `4 < B <= 8 && 6 < A <= 10 && 44 < A * B <= 46`, so we can know A = 9, B = 5.

#### 3.69
A. Through `lea (%rdi,%rdi,4),%rax; lea (%rsi,%rax,8),%rax; mov 0x8(%rax),%rdx`, we can get `*ap = *(bp + 8 + 40 * i);`.

So the alignment of `b_struct` is 8 and size of `a_struct` is 40, then we can conclude that CNT = (0x120 - align) / sizeof(a_struct) = (288 - 8) / 40 = 7.

B.
```
typedef struct {
    long val;
    long x[4];
} a_struct;
```

#### 3.70
A.
| field   | offset|
| ------- | ----- |
| e1.p    | 0     |
| e1.y    | 8     |
| e2.x    | 0     |
| e2.next | 8     |

B. 16 types.

C.
```c
void proc (union ele *up) {
    up->e2.x = *(up->e2.next->e1.p) - up->e2.next->e1.y;
}
```

#### 3.72
A. The computation of `s2` can be explained in mathematical terms as follows:
   - `%rdi` holds the value of `n`, which represents the number of elements in the array `p`.
   - `30(,%rdi,8)` calculates `n*8 + 30`, which determines the total number of bytes needed for the array `p` (assuming each element of `p` requires 8 bytes).
   - The result is stored in `%rax`.
   - `andq $-16, %rax` performs a bitwise AND operation with `-16` (which is equivalent to `0xFFFFFFFFFFFFFFF0`) on `%rax`. This operation aligns `%rax` to the nearest multiple of 16 (rounding down).
   - The aligned value is subtracted from `%rsp` using `subq %rax, %rsp`, effectively allocating space for the array `p`.
   - Thus, `s2` represents the stack pointer after allocating space for `p` and aligning it to a multiple of 16.

B. The computation of `p` can be explained in mathematical terms as follows:
   - `%rsp` holds the value of `s2`, which represents the stack pointer after allocating space for `p` and aligning it to a multiple of 16.
   - `15(%rsp)` calculates `%rsp + 15`, which points to the address just after the allocated space for `p`.
   - The result is stored in `%r8`, which represents the start address of `p`.

C. To find the minimum and maximum values of `e1`, we need to consider the space between the end of array `p` and `s1`. Since the size of `p` is `n * sizeof(long *)`, and each element requires `sizeof(long *)` bytes, the minimum value of `e1` occurs when `s1` is immediately after the end of `p`, and the maximum value of `e1` occurs when there is no extra space between the end of `p` and `s1`.
   - Minimum value of `e1`: When there is no extra space, `e1` is 0.
   - Maximum value of `e1`: When `s1` is immediately after the end of `p`, `e1` is `sizeof(long *)`.

D. The code guarantees the following alignment properties for the values of `s2` and `p`:
   - The value of `s2` is aligned to a multiple of 16 bytes due to the `andq $-16, %rax` operation, which rounds down the address.
   - The value of `p` points to an address that is aligned to a multiple of 16 bytes, as `%r8` is obtained by adding 15 to `%rsp` and aligning it to the nearest multiple of 16.

Thus, both `s2` and `p` have addresses that satisfy 16-byte alignment requirements.

#### 3.75
A. Complex arguments are passed using the SSE (Streaming SIMD Extensions) registers.

B. The real part is stored in `%xmm0` and the imaginary part is stored in `%xmm1`.
