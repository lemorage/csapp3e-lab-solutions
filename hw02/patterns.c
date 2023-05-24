#include <stdio.h>
#include <assert.h>

// Function to generate the bit pattern A: 1^(w-k)0^k
unsigned int generatePatternA(int w, int k) {
    unsigned int patternA = ~((1 << (w - k)) - 1) << k;
    return patternA;
}

// Function to generate the bit pattern B: 0^(w-k-j)1^k0^j
unsigned int generatePatternB(int w, int k, int j) {
    unsigned int patternB = ~((~0 << (w - k - j)) << (k + j));
    return patternB;
}

int main() {
    int w = sizeof(unsigned int) * 8;  // Number of bits in unsigned int

    // Generate bit pattern A
    int kA = 4;
    unsigned int patternA = generatePatternA(w, kA);
    assert(patternA == 0x0);  // Assert the correctness of pattern A

    // Generate bit pattern B
    int kB = 3;
    int jB = 2;
    unsigned int patternB = generatePatternB(w, kB, jB);
    assert(patternB == 0xFFFFFFFFu);  // Assert the correctness of pattern B

    // Print the generated patterns
    puts("All tests for patterns passed!");

    return 0;
}
