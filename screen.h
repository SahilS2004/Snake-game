#ifndef SCREEN_H
#define SCREEN_H

/**
 * Custom screen drawing library using ANSI escape codes.
 * Terminal manipulation.
 */

/* Clear the entire terminal screen and home the cursor */
void clear_screen(void);

/* Move terminal cursor to position (x, y). (1, 1) is top-left. */
void move_cursor(int x, int y);

/* Draw a character at current cursor position */
void draw_char(char c);

/* Draw a null-terminated string at current cursor position */
void draw_string(const char* s);

#endif /* SCREEN_H */
