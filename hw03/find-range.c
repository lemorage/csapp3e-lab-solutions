typedef enum {NEG, ZERO, POS, OTHER} range_t;

/*
3.73

section .text
global find_range_asm

find_range_asm:
    movaps xmm1, xmm0     ; Copy the argument x into xmm1
    movaps xmm2, xmm1     ; Copy xmm1 for comparison

    cmpnltps xmm1, xmm0   ; Compare xmm1 with x to check if x < 0

    jz check_zero         ; Jump to check_zero if x == 0
    jnz check_positive    ; Jump to check_positive if x > 0

    mov eax, 0            ; If x < 0, set result to NEG
    ret

check_zero:
    ucomiss xmm2, xmm0    ; Compare xmm2 with x to check if x == 0

    jp pos_or_nan         ; Jump to pos_or_nan if x is NaN
    je done               ; Jump to done if x == 0

pos_or_nan:
    mov eax, 1            ; Set result to ZERO if x is NaN or pos_or_nan
    ret

check_positive:
    add eax, 2            ; Increment result by 2 (POS for x > 0, OTHER for NaN)
    ret

done:
    ret
*/
range_t find_range(float x)
{
    range_t result;
    
    asm (
        "movaps %1, %%xmm1 \n"
        "movaps %%xmm1, %%xmm2 \n"
        "cmpnltps %1, %%xmm0 \n"
        "jz 0f \n"
        "jnz 1f \n"
        "mov $0, %0 \n"
        "ret \n"
        "0: \n"
        "ucomiss %%xmm2, %%xmm0 \n"
        "jp 2f \n"
        "je 3f \n"
        "2: \n"
        "mov $1, %0 \n"
        "ret \n"
        "3: \n"
        "add $2, %0 \n"
        "ret \n"
        "1: \n"
        : "=r" (result)
        : "x" (x)
    );
    
    return result;
}


/*
3.74

find_range:
    vxorps %xmm1, %xmm1, %xmm1    ; Clear xmm1 register
    ucomiss %xmm0, %xmm1          ; Compare xmm0 with 0
    jbe .L1                       ; Jump if xmm0 <= 0
    movl $POS, %eax               ; Set result = POS
    jp .L2                        ; Jump if xmm0 is NaN
    ret                           ; Return

.L1:
    seta %al                      ; Set %al if xmm0 > 0
    addl $2, %eax                 ; Add 2 to result (POS if xmm0 > 0, OTHER if xmm0 is NaN)
.L2:
    ret                           ; Return
*/

range_t find_range_br(float x)
{
    range_t result;

    asm (
        "vxorps %%xmm1, %%xmm1, %%xmm1\n\t"   // Clear xmm1 register
        "ucomiss %1, %%xmm1\n\t"              // Compare xmm0 with 0
        "jbe 0f\n\t"                          // Jump if xmm0 <= 0
        "movl $%c[POS], %0\n\t"               // Set result = POS
        "jp 1f\n\t"                           // Jump if xmm0 is NaN
        "ret\n"
        "0:\n\t"
        "seta %%al\n\t"                       // Set %al if xmm0 > 0
        "addl $2, %0\n\t"                     // Add 2 to result (POS if xmm0 > 0, OTHER if xmm0 is NaN)
        "1:\n\t"
        : "=r" (result)
        : "x" (x), [POS] "i" (POS)
        : "%xmm1", "%al"
    );

    return result;
}

int main()
{
    float x = 2.5;
    range_t range = find_range(x);

    // Test the result
    switch (range) {
        case NEG:
            printf("Range: NEG\n");
            break;
        case ZERO:
            printf("Range: ZERO\n");
            break;
        case POS:
            printf("Range: POS\n");
            break;
        case OTHER:
            printf("Range: OTHER\n");
            break;
        default:
            printf("Invalid range\n");
            break;
    }

    return 0;
}
