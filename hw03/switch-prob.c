long switch_prob(long x, long n) {
    switch (n) {
        case 0x83ee3c:
            x -= 0x3c;
            break;
        case 0x83fe05:
            if (x > 0x29)
                return x;
            else
                return 0xf5f8;
        case 0x29:
            x *= 8;
            break;
        case 0x24f5f8:
            x -= (x * x);
            x += 0x4b;
            break;
        case 0x8d04fd:
            x = (x >> 3);
            break;
        case 0x89f8:
            x = (x >> 4);
            break;
        default:
            x *= x;
            x += 0x4b;
            break;
    }
    
    return x;
}
