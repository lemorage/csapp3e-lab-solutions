#### 7.6
| Symbol  | `swap.o` `.symtab` entry? | Symbol type | Module where defined | Section |
| :-----: | :-----------------------: | :---------: | :------------------: | :-----: |
|  `buf`  |            YES            |   extern    |        `m.o`         | `.data` |
| `bufp0` |            YES            |   global    |       `swap.o`       | `.data` |
| `bufp1` |            YES            |   global    |       `swap.o`       | `.bss`  |
| `swap`  |            YES            |   global    |       `swap.o`       | `.text` |
| `temp`  |            NO             |      —      |          —           |    —    |
| `incr`  |            YES            |   global    |          —           | `.text` |
| `count` |            NO             |      —      |          —           |    —    |

#### 7.7
```c
/* bar5.c */
double x;

void f()
{
    // x = -0.0 /* Delete this line */
}
```

#### 7.8
A.

(a) ERROR\
(b) ERROR

B.

(a) REF(x.1) -> DEF(x.UNKNOWN)\
(b) REF(x.2) -> DEF(x.UNKNOWN)

C.

(a) ERROR\
(b) ERROR

#### 7.9
This is because of how linkers resolve duplicate symbol names in linux compilation systems. Since `int main() {}` in `foo6.c` is a global function, and `char main` in `bar6.c` is an uninitialized global variable, so `char main` is ignored at the compile time. At runtime, when we execute the main program, function `p2` is invoked, and `char main` overwrites the original data type of `main`, so the original value stored in `main` is printed as a character value.

To see why `0x48` is printed, we can use `objdump -d main` to see the details of main function.

#### 7.10
A. `linux> gcc p.o libx.a`

B. `linux> gcc libx.a liby.a libx.a p.o`

C. `linux> gcc libz.a libx.a liby.a libx.a p.o`

#### 7.11
The remaining 8 bytes in the segment correspond to `.bss` data that will be initialized to zero at run time.

#### 7.12
A.
Since `ADDR(s) = ADDR(.text) = 0x4004e0` and `ADDR(r.symbol) = ADDR(swap) = 0x4004f8`, we can calculate the run-time address of the reference `refaddr = ADDR(s) + r.offset = 0x4004e0 + 0xa = 0x4004ea`.

It then updates the reference so that it will point to the swap routine at run time: `*refptr = (unsigned) (ADDR(r.symbol) + r.addend - refaddr) = (unsigned) (0x4004f8 + (-4) - 0x4004ea) = 0xa`

So the value of the relocated reference to `swap` in the `callq` instruction is `0xa`.

B.
Using the same algorithms as above, `refaddr = ADDR(.text) + r.offset = 0x4004d0 + 0xa = 0x4004da`, `*refptr = (unsigned) (ADDR(r.symbol) + r.addend - refaddr) = (unsigned) (0x400500 + (-4) - 0x4004da) = 0x22`.

So the value of the relocated reference to `swap` in the `callq` instruction is `0x22`.

#### 7.13
A. See `task.sh` for details.

B.
The `-Og` flag in GCC enables optimization for debugging, and the `-g` flag includes debugging information in the executable. To see if there is really a difference, we can create an example program, compile it and use `diff` command to see the differences.

- Create a simple C program, e.g., `example.c`, with some code.
2. Compile it with `-Og` and `-g` flags separately:
```bash
gcc -Og -c example.c -o example_Og.o
gcc -Og -g -c example.c -o example_Og_g.o
```
3. Disassemble the object files to obtain assembly code:
```bash
objdump -d example_Og.o > example_Og.asm
objdump -d example_Og_g.o > example_Og_g.asm
```
4. Use the `diff` command to compare the assembly files:
```bash
diff example_Og.asm example_Og_g.asm
```

If there are no differences between the assembly files, it means that both compilation options produced the same executable code.


C. See `task.sh` for details.