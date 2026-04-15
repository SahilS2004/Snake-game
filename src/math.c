#include "math.h"



static unsigned int next_seed = 1;

int mul(int a, int b) {
    return a * b;
}

int div(int a, int b) {
    if (b == 0) return 0;
    return a / b;
}

int mod(int a, int b) {
    if (b == 0) return 0;
    return a % b;
}

int abs(int n) {
    return (n < 0) ? -n : n;
}

void init_rand(unsigned int seed) {
    next_seed = seed;
}

static int custom_rand(void) {
    next_seed = next_seed * 1103515245 + 12345;
    return (unsigned int)(next_seed / 65536) % 32768;
}

int random_range(int min, int max) {
    if (min >= max) return min;
    int r = custom_rand();
    return min + (mod(r, (max - min + 1)));
}
