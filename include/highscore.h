#ifndef HIGHSCORE_H
#define HIGHSCORE_H

/**
 * Persistent high score manager.
 * Reads and writes the all-time high score to a local file.
 */

#define HIGHSCORE_FILE ".snake_highscore"

/* Load the saved high score from disk. Returns 0 if no file exists. */
int load_highscore(void);

/* Save a new high score to disk. Only writes if score > current saved value. */
void save_highscore(int score);

#endif /* HIGHSCORE_H */
