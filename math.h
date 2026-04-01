#ifndef MATH_H
#define MATH_H

/**
 * Custom math library.
 * Functions to replace standard libc math operations and random numbers.
 */

/* Multiplies two integers */
int mul(int a, int b);

/* Divides two integers */
int div(int a, int b);

/* Returns the remainder of division of two integers */
int mod(int a, int b);

/* Returns the absolute value of an integer */
int abs(int n);

/* Initializes the pseudo-random number generator with a seed */
void init_rand(unsigned int seed);

/* Returns a pseudo-random integer between min and max inclusive */
int random_range(int min, int max);

#endif /* MATH_H */
