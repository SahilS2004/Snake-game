#ifndef MENU_H
#define MENU_H

/**
 * Terminal menu / dashboard system.
 * Displays a title screen with selectable options using arrow-pointer navigation.
 */

/* Menu selection results */
#define MENU_START      0
#define MENU_HIGHSCORE  1
#define MENU_QUIT       2

/**
 * Display the main menu dashboard and wait for user selection.
 * Uses W/S or arrow keys to move the pointer, Enter/D to confirm.
 * Returns one of: MENU_START, MENU_HIGHSCORE, MENU_QUIT
 */
int show_menu(int high_score);

#endif /* MENU_H */
