/* Bubble sort: Pointer version */
void bubble_p(long *data, long count) {
    long i, last;
    for (last = count - 1; last > 0; --last) {
        for (i = 0; i < last; ++i) {
            if (*(data + i + 1) < *(data + i)) {
                long t = *(data + i + 1);
                *(data + i + 1) = *(data + i);
                *(data + i) = t;
            }
        }
    }
}