#include <stdio.h>

int int_shifts_are_arithmetic()
{
    int x = -1; // a signed integer with all bits set to 1
    return (x >> 1) < 0;
}

int main()
{
    if (int_shifts_are_arithmetic)
        printf("This machine uses arithmetic right shifts for int data type.\n");
    else
        printf("This machine does not use arithmetic right shifts for int data type.\n");

    return 0;
}