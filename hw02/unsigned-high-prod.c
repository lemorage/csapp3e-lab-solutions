#include <stdint.h>

int signed_high_prod(int x, int y) {
    int64_t result = (int64_t)x * y;
    return result >> 32;
}

unsigned unsigned_high_prod(unsigned x, unsigned y) {
    int signed_x = (int)x;
    int signed_y = (int)y;
    int signed_result = signed_high_prod(signed_x, signed_y);
    unsigned unsigned_result = (unsigned)signed_result;
    return unsigned_result;
}

int main()
{
    return 0;
}