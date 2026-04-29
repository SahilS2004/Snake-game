#include "highscore.h"
#include "string.h"
#include <stdio.h>

/**
 * Persistent high score implementation.
 * Uses a simple flat file to store the integer high score.
 */

int load_highscore(void) {
    FILE* f = fopen(HIGHSCORE_FILE, "r");
    if (!f) return 0;

    char buf[32];
    int i = 0;
    int ch;

    while ((ch = fgetc(f)) != EOF && i < 31) {
        if (ch >= '0' && ch <= '9') {
            buf[i++] = (char)ch;
        } else {
            break;
        }
    }
    buf[i] = '\0';
    fclose(f);

    return str_to_int(buf);
}

void save_highscore(int score) {
    int current = load_highscore();
    if (score <= current) return;

    FILE* f = fopen(HIGHSCORE_FILE, "w");
    if (!f) return;

    char buf[32];
    int_to_str(score, buf);
    fprintf(f, "%s\n", buf);
    fclose(f);
}
