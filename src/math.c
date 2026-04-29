#include "math.h"

/**
 * Custom math module — reimplemented with basic binary shifters.
 *
 * Every arithmetic operation avoids hardware MUL/DIV instructions:
 *   mul()  — shift-and-add (Russian peasant multiplication)
 *   div()  — bitwise long division (restoring method)
 *   mod()  — remainder from bitwise long division
 *   abs()  — sign-bit mask with XOR
 *
 * PRNG uses a Linear Congruential Generator driven entirely
 * by the bitwise mul and div routines above.
 */

static unsigned int next_seed = 1;

/**
 * Multiplication using bitwise shift-and-add.
 */
int mul(int a, int b) {
    int res = 0;
    unsigned int abs_a = (a < 0) ? -a : a;
    unsigned int abs_b = (b < 0) ? -b : b;
    
    while (abs_b > 0) {
        if (abs_b & 1) {
            res += abs_a;
        }
        abs_a <<= 1;
        abs_b >>= 1;
    }
    
    return ((a < 0) ^ (b < 0)) ? -res : res;
}

/**
 * Helper for division and modulo using bitwise long division.
 */
static void bitwise_div_mod(int dividend, int divisor, int* quotient, int* remainder) {
    if (divisor == 0) {
        if (quotient) *quotient = 0;
        if (remainder) *remainder = 0;
        return;
    }

    unsigned int a = (dividend < 0) ? -dividend : dividend;
    unsigned int b = (divisor < 0) ? -divisor : divisor;
    unsigned int q = 0;
    unsigned int r = 0;

    for (int i = 31; i >= 0; i--) {
        r = (r << 1) | ((a >> i) & 1);
        if (r >= b) {
            r -= b;
            q |= (1U << i);
        }
    }

    if (quotient) *quotient = ((dividend < 0) ^ (divisor < 0)) ? -(int)q : (int)q;
    if (remainder) *remainder = (dividend < 0) ? -(int)r : (int)r;
}

int div(int a, int b) {
    int q;
    bitwise_div_mod(a, b, &q, 0);
    return q;
}

int mod(int a, int b) {
    int r;
    bitwise_div_mod(a, b, 0, &r);
    return r;
}

/**
 * Absolute value using bitwise manipulation.
 * Uses (sizeof(int) << 3) to get 32 bits without using multiplication.
 */
int abs(int n) {
    int const mask = n >> ((sizeof(int) << 3) - 1);
    return (n + mask) ^ mask;
}

void init_rand(unsigned int seed) {
    next_seed = seed;
}

static int custom_rand(void) {
    // Linear Congruential Generator: next = (a * seed + c) % m
    // Using bitwise mul for a * seed
    next_seed = mul(next_seed, 1103515245) + 12345;
    
    // Use bitwise div and mod for the result
    int temp_q;
    bitwise_div_mod((int)(next_seed >> 16), 32768, 0, &temp_q);
    return temp_q < 0 ? -temp_q : temp_q;
}

int random_range(int min, int max) {
    if (min >= max) return min;
    int r = custom_rand();
    int range = max - min + 1;
    int remainder;
    bitwise_div_mod(r, range, 0, &remainder);
    return min + (remainder < 0 ? -remainder : remainder);
}
