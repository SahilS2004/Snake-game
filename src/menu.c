#include "menu.h"
#include "screen.h"
#include "string.h"
#include "keyboard.h"
#include <unistd.h>

/**
 * Terminal menu / dashboard implementation.
 * Renders an ASCII art title, colored menu options, and an
 * interactive arrow pointer for selection.
 */

#define MENU_COUNT   3
#define MENU_X       16
#define MENU_Y_START 14

static const char* menu_labels[MENU_COUNT] = {
    "START GAME",
    "HIGH SCORE",
    "QUIT"
};

static void draw_menu(int selected, int high_score) {
    clear_screen();

    /* ── ASCII art title (bright green, bold) ── */
    set_bold();
    set_color(COLOR_BRIGHT_GREEN);

    move_cursor(10, 2);
    draw_string("  ____              _        ");
    move_cursor(10, 3);
    draw_string(" / ___|_ __   __ _ | | _____ ");
    move_cursor(10, 4);
    draw_string(" \\___ \\ '_ \\ / _` || |/ / _ \\");
    move_cursor(10, 5);
    draw_string("  ___) | | | | (_| ||   <  __/");
    move_cursor(10, 6);
    draw_string(" |____/|_| |_|\\__,_||_|\\_\\___|");
    reset_color();

    /* ── Subtitle ── */
    move_cursor(14, 8);
    set_color(COLOR_CYAN);
    draw_string("~ Terminal Edition ~");
    reset_color();

    /* ── Divider ── */
    move_cursor(10, 10);
    set_color(COLOR_BLUE);
    draw_string("\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90"
                "\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90"
                "\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90"
                "\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90"
                "\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90"
                "\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90"); /* 30x ═ */
    reset_color();

    /* ── High Score banner ── */
    move_cursor(16, 12);
    set_bold();
    set_color(COLOR_YELLOW);
    draw_string("\xe2\x98\x85 "); /* ★ */
    draw_string("Best: ");
    char hs[32];
    int_to_str(high_score, hs);
    draw_string(hs);
    reset_color();

    /* ── Menu options ── */
    for (int i = 0; i < MENU_COUNT; i++) {
        move_cursor(MENU_X, MENU_Y_START + i * 2);

        if (i == selected) {
            set_bold();
            set_color(COLOR_BRIGHT_GREEN);
            draw_string("\xe2\x96\xb6 "); /* ▶ pointer */
            draw_string(menu_labels[i]);
            reset_color();
        } else {
            set_color(COLOR_WHITE);
            draw_string("  ");
            draw_string(menu_labels[i]);
            reset_color();
        }
    }

    /* ── Footer hint ── */
    move_cursor(8, MENU_Y_START + MENU_COUNT * 2 + 1);
    set_color(COLOR_BLUE);
    draw_string("[W/S or \xe2\x86\x91/\xe2\x86\x93 to move | Enter/D to select]");
    reset_color();

    flush_screen();
}

int show_menu(int high_score) {
    int selected = 0;

    draw_menu(selected, high_score);

    while (1) {
        char ch = keyPressed();

        if (ch == 'w' || ch == 'W') {
            if (selected > 0) {
                selected--;
                draw_menu(selected, high_score);
            }
        } else if (ch == 's' || ch == 'S') {
            if (selected < MENU_COUNT - 1) {
                selected++;
                draw_menu(selected, high_score);
            }
        } else if (ch == 'd' || ch == 'D' || ch == '\n' || ch == '\r') {
            return selected;
        } else if (ch == 'q' || ch == 'Q') {
            return MENU_QUIT;
        }

        usleep(50000); /* 50ms poll interval */
    }
}
