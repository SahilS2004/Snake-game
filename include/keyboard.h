#ifndef KEYBOARD_H
#define KEYBOARD_H

/**
 * Custom keyboard input library.
 * Configures the terminal to provide non-blocking input.
 */

/* Sets terminal up for non-blocking, raw input */
void init_keyboard(void);

/* Checks if a key was pressed and returns its ASCII value, or 0 if none */
char keyPressed(void);

/* Resets terminal to original settings */
void reset_keyboard(void);

#endif /* KEYBOARD_H */
