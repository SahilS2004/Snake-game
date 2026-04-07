#include "keyboard.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * Custom keyboard library implementation.
 * Configures termios settings to provide non-blocking, non-echoing input.
 */

static struct termios orig_termios;

void init_keyboard(void) {
    struct termios new_termios;
    
    // Save original terminal settings for restoration on exit
    tcgetattr(STDIN_FILENO, &orig_termios);
    
    new_termios = orig_termios;
    // Disable canonical mode (line buffering) and local echo
    new_termios.c_lflag &= ~(ICANON | ECHO);
    
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    
    // Set non-blocking mode for stdin
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

char keyPressed(void) {
    char ch;
    // Non-blocking read (returns 1 on success, <1 otherwise)
    if (read(STDIN_FILENO, &ch, 1) == 1) {
        return ch;
    }
    return 0;
}

void reset_keyboard(void) {
    // Restore original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}
