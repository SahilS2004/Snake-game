#ifndef STRING_H
#define STRING_H

/**
 * Custom string library.
 * Functions to replace standard libc string functions.
 */

/* Return the length of a null-terminated string */
int str_len(const char* s);

/* Copy a null-terminated string from src to dest */
void str_copy(char* dest, const char* src);

/* Compare two strings. Returns 0 if equal, non-zero otherwise */
int str_compare(const char* s1, const char* s2);

/* Convert an integer to its string representation */
void int_to_str(int n, char* s);

/* Convert a string representation of an integer to an int value */
int str_to_int(const char* s);

#endif /* STRING_H */
