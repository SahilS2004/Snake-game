#include <unistd.h>
#include "game.h"
#include "highscore.h"
#include "keyboard.h"
#include "menu.h"
#include "screen.h"
#include "string.h"

/**
 * Main application entry point.
 * Coordinates the menu dashboard, game loop, and graceful termination.
 */

static void play_game(void) {
    GameState state;

    // Initialize game systems
    init_game(&state);

    // Real-time game loop
    while (!state.game_over) {
        char ch = keyPressed();

        if (ch == 'q' || ch == 'Q') {
            break;
        }

        update_game(&state, ch);
        render_game(&state);

        usleep(200000);
    }

    // Persist high score
    save_highscore(state.score);

    // Show game over summary for 2 seconds
    render_game(&state);
    usleep(2000000);
}

static void show_highscore_screen(int high_score) {
    clear_screen();

    move_cursor(14, 4);
    set_bold();
    set_color(COLOR_CYAN);
    draw_string("\xe2\x95\x94\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90"
                "\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90"
                "\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90"
                "\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x97"); /* ╔══════════════════╗ */
    reset_color();

    move_cursor(14, 5);
    set_bold();
    set_color(COLOR_CYAN);
    draw_string("\xe2\x95\x91");  /* ║ */
    reset_color();
    set_bold();
    set_color(COLOR_YELLOW);
    draw_string("  \xe2\x98\x85 HIGH SCORE \xe2\x98\x85  ");
    reset_color();
    set_bold();
    set_color(COLOR_CYAN);
    draw_string("\xe2\x95\x91");  /* ║ */
    reset_color();

    move_cursor(14, 6);
    set_bold();
    set_color(COLOR_CYAN);
    draw_string("\xe2\x95\x9f\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80"
                "\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80"
                "\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80"
                "\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x95\xa2"); /* ╟──────────────────╢ */
    reset_color();

    move_cursor(14, 7);
    set_bold();
    set_color(COLOR_CYAN);
    draw_string("\xe2\x95\x91");  /* ║ */
    reset_color();

    // Center the score value
    char hs[32];
    int_to_str(high_score, hs);
    int len = str_len(hs);
    int pad = (18 - len) / 2;
    for (int i = 0; i < pad; i++) draw_char(' ');
    set_bold();
    set_color(COLOR_BRIGHT_GREEN);
    draw_string(hs);
    reset_color();
    for (int i = 0; i < 18 - pad - len; i++) draw_char(' ');

    set_bold();
    set_color(COLOR_CYAN);
    draw_string("\xe2\x95\x91");  /* ║ */
    reset_color();

    move_cursor(14, 8);
    set_bold();
    set_color(COLOR_CYAN);
    draw_string("\xe2\x95\x9a\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90"
                "\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90"
                "\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90"
                "\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x9d"); /* ╚══════════════════╝ */
    reset_color();

    move_cursor(12, 11);
    set_color(COLOR_BLUE);
    draw_string("[Press any key to return]");
    reset_color();
    flush_screen();

    // Wait for keypress
    while (1) {
        char ch = keyPressed();
        if (ch != 0) break;
        usleep(50000);
    }
}

int main(void) {
    // Setup terminal
    init_keyboard();

    int running = 1;

    while (running) {
        int hs = load_highscore();
        int choice = show_menu(hs);

        switch (choice) {
            case MENU_START:
                play_game();
                break;

            case MENU_HIGHSCORE:
                show_highscore_screen(load_highscore());
                break;

            case MENU_QUIT:
                running = 0;
                break;
        }
    }

    // Graceful exit
    reset_keyboard();
    clear_screen();
    move_cursor(1, 1);

    set_bold();
    set_color(COLOR_GREEN);
    draw_string("Thanks for playing! ");
    reset_color();
    draw_string("\xf0\x9f\x90\x8d\n"); /* 🐍 */
    flush_screen();

    return 0;
}
