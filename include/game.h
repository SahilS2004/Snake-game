#ifndef GAME_H
#define GAME_H

/**
 * Snake game core logic header.
 * Real-time mechanics and snake body management.
 */

#define GAME_WIDTH 40
#define GAME_HEIGHT 20
#define BOARD_X_OFFSET 4
#define BOARD_Y_OFFSET 2

typedef enum {
    UP, DOWN, LEFT, RIGHT
} Direction;

typedef struct SnakeNode {
    int x, y;
    struct SnakeNode* next;
} SnakeNode;

typedef struct GameState {
    SnakeNode* head;
    SnakeNode* tail;
    int food_x, food_y;
    Direction dir;
    int score;
    int game_over;
} GameState;

/* Initialize new game state */
void init_game(GameState* state);

/* Update game state based on inputs and time elapsed */
void update_game(GameState* state, char input);

/* Render current state to screen */
void render_game(GameState* state);

#endif /* GAME_H */
