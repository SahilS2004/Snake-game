#include "screen.h"
#include <stdio.h>

/**
 * Custom screen drawing implementation.
 * Using standard ANSI escape codes for terminal control.
 */

void clear_screen(void) {
    // \033[2J: clear screen, \033[H: move home
    printf("\033[2J\033[H");
    fflush(stdout);
}

void move_cursor(int x, int y) {
    // \033[y;xH: move to row y, column x (ANSI is 1-indexed)
    printf("\033[%d;%dH", y, x);
    fflush(stdout);
}

void draw_char(char c) {
    putchar(c);
    fflush(stdout);
}

void draw_string(const char* s) {
    printf("%s", s);
    fflush(stdout);
}
