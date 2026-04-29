#ifndef MATH_H
#define MATH_H

/**
 * Custom math library — reimplemented with basic binary shifters.
 * All arithmetic (mul, div, mod, abs) uses only bitwise shift,
 * AND, OR, and XOR operations. No hardware multiply/divide.
 */

/* Multiplies two integers using shift-and-add */
int mul(int a, int b);

/* Divides two integers using bitwise long division */
int div(int a, int b);

/* Returns the remainder using bitwise long division */
int mod(int a, int b);

/* Returns the absolute value using sign-bit mask */
int abs(int n);

/* Initializes the pseudo-random number generator with a seed */
void init_rand(unsigned int seed);

/* Returns a pseudo-random integer between min and max inclusive */
int random_range(int min, int max);

#endif /* MATH_H */
