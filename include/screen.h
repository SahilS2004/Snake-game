#ifndef SCREEN_H
#define SCREEN_H

/**
 * Custom screen drawing library using ANSI escape codes.
 * Terminal manipulation and color rendering.
 */

/* ANSI foreground color codes */
#define COLOR_RESET   0
#define COLOR_RED     31
#define COLOR_GREEN   32
#define COLOR_YELLOW  33
#define COLOR_BLUE    34
#define COLOR_MAGENTA 35
#define COLOR_CYAN    36
#define COLOR_WHITE   37

/* ANSI bright/bold foreground color codes */
#define COLOR_BRIGHT_RED     91
#define COLOR_BRIGHT_GREEN   92
#define COLOR_BRIGHT_YELLOW  93
#define COLOR_BRIGHT_CYAN    96
#define COLOR_BRIGHT_WHITE   97

/* Clear the entire terminal screen and home the cursor */
void clear_screen(void);

/* Move terminal cursor to position (x, y). (1, 1) is top-left. */
void move_cursor(int x, int y);

/* Set the foreground text color using an ANSI color code */
void set_color(int color);

/* Enable bold/bright text attribute */
void set_bold(void);

/* Reset all text attributes (color, bold) to default */
void reset_color(void);

/* Draw a character at current cursor position */
void draw_char(char c);

/* Draw a null-terminated string at current cursor position */
void draw_string(const char* s);

/* Flush terminal output buffer */
void flush_screen(void);

#endif /* SCREEN_H */
