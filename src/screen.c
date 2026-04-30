#include "screen.h"
#include <stdio.h>

/**
 * Custom screen drawing implementation.
 * Using standard ANSI escape codes for terminal control and color.
 */

void clear_screen(void) {
    // \x1b[H: move home, \x1b[J: clear from cursor to end of screen
    printf("\x1b[H\x1b[J");
    fflush(stdout);
}

void move_cursor(int x, int y) {
    // \x1b[y;xH: move to row y, column x (ANSI is 1-indexed)
    printf("\x1b[%d;%dH", y, x);
    fflush(stdout);
}

void set_color(int color) {
    printf("\x1b[%dm", color);
}

void set_bold(void) {
    printf("\x1b[1m");
}

void reset_color(void) {
    printf("\x1b[0m");
}

void draw_char(char c) {
    putchar(c);
}

void draw_string(const char* s) {
    printf("%s", s);
}

void flush_screen(void) {
    fflush(stdout);
}
