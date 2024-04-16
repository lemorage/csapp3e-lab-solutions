#### Pre-Launch

In the preliminary exploration, we can see the presence of an executable program named "bomb".

To gain insights into its functionality, we can utilize commands such as `objdump -t bomb | less` or `strings bomb` for a quick overview. Additionally, we can generate a detailed assembly code listing using `objdump -d bomb > foo.txt`. The resulting file, `foo.txt`, contains the entire assembly code for the program.

And we can observe, each of the six phases of the bomb program concludes with the instruction `callq 40143a <explode_bomb>`, signifying the Exploding Bomb function. What we need to do is to allow the program to execute and pause before reaching this critical point.

#### Phase 1

Upon initiating the process, we open the GDB with the command `gdb bomb` and establish a breakpoint using `break explode_bomb`. Executing the program with `run` automatically halts execution at the designated breakpoint. Using the `disas` command, we inspect the assembly code for the `phase_1` function:

```assembly
(gdb) disas phase_1
Dump of assembler code for function phase_1:
   0x0000000000400ee0 <+0>:     sub    $0x8,%rsp
   0x0000000000400ee4 <+4>:     mov    $0x402400,%esi
   0x0000000000400ee9 <+9>:     callq  0x401338 <strings_not_equal>
   0x0000000000400eee <+14>:    test   %eax,%eax
   0x0000000000400ef0 <+16>:    je     0x400ef7 <phase_1+23>
   0x0000000000400ef2 <+18>:    callq  0x40143a <explode_bomb>
   0x0000000000400ef7 <+23>:    add    $0x8,%rsp
   0x0000000000400efb <+27>:    retq 
End of assembler dump.
```

1. **`sub $0x8,%rsp`**: This instruction subtracts 8 from the stack pointer (`%rsp`). It's likely reserving space on the stack for local variables or temporary storage.

2. **`mov $0x402400,%esi`**: This moves the immediate value `0x402400` into the `%esi` register.

3. **`callq 0x401338 <strings_not_equal>`**: This calls the function at address `0x401338`, which is named `strings_not_equal`. The `%esi` register likely contains a pointer to a string that is being passed as an argument to this function.

4. **`test %eax,%eax`**: This tests the value in the `%eax` register. `%eax` is being bitwise ANDed with itself. The primary purpose of this operation is to set the zero flag (`ZF`) in the FLAGS register.

5. **`je 0x400ef7 <phase_1+23>`**: This jumps to the address `0x400ef7` if the zero flag is set, meaning that the previous test (`test %eax,%eax`) resulted in equality (zero).

6. **`callq 0x40143a <explode_bomb>`**: This calls the `explode_bomb` function if the zero flag is not set, indicating that the strings are not equal.

So, in essence, the `phase_1` function is to put something in the `%esi` register, and call `<strings_not_equal>` function to compare the user input with it, if they are not the same, call `<explode_bomb>`.

Now we only need to inspect the value in `%esi` register, in order to defuse the first bomb.

```cmd
(gdb) x $esi
0x402400:       0x64726f42
(gdb) x/s $esi
0x402400:       "Border relations with Canada have never been better."
(gdb) 
```

#### Phase 2
