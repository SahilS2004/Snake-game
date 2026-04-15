#include <stdio.h>
#include "game.h"
#include "memory.h"
#include "math.h"
#include "screen.h"
#include "string.h"

/**
 * Snake game logic implementation.
 * Custom memory allocation for snake nodes and non-blocking input handling.
 */

// Global constant to help with the game board dimensions
#define BOARD_X_OFFSET 4
#define BOARD_Y_OFFSET 2

static void spawn_food(GameState* state) {
    state->food_x = random_range(2, GAME_WIDTH - 1);
    state->food_y = random_range(2, GAME_HEIGHT - 1);
    
    // Check food doesn't overlap snake
    SnakeNode* curr = state->head;
    while(curr) {
        if(curr->x == state->food_x && curr->y == state->food_y) {
            spawn_food(state); // Collision, try again
            return;
        }
        curr = curr->next;
    }
}

void init_game(GameState* state) {
    init_memory(); 
    init_rand(42); // Simple static seed
    
    state->dir = RIGHT;
    state->score = 0;
    state->game_over = 0;
    state->death_reason = 0;
    
    // Allocate starting head
    state->head = (SnakeNode*)alloc(sizeof(SnakeNode));
    state->head->x = GAME_WIDTH / 2;
    state->head->y = GAME_HEIGHT / 2;
    state->head->next = 0;
    state->tail = state->head;
    
    // Add two initial body segments
    for(int i = 0; i < 3; i++) {
        SnakeNode* body = (SnakeNode*)alloc(sizeof(SnakeNode));
        body->x = state->head->x - (i + 1);
        body->y = state->head->y;
        body->next = 0;
        state->tail->next = body;
        state->tail = body;
    }
    
    spawn_food(state);
}

void update_game(GameState* state, char input) {
    if (state->game_over) return;
    
    // Update direction based on character input (W/A/S/D)
    if (input == 'w' || input == 'W') {
        if (state->dir != DOWN) state->dir = UP;
    } else if (input == 's' || input == 'S') {
        if (state->dir != UP) state->dir = DOWN;
    } else if (input == 'a' || input == 'A') {
        if (state->dir != RIGHT) state->dir = LEFT;
    } else if (input == 'd' || input == 'D') {
        if (state->dir != LEFT) state->dir = RIGHT;
    }
    
    // Calculate new head position
    int new_x = state->head->x;
    int new_y = state->head->y;
    
    if (state->dir == UP) new_y--;
    else if (state->dir == DOWN) new_y++;
    else if (state->dir == LEFT) new_x--;
    else if (state->dir == RIGHT) new_x++;
    
    // Wall collision
    if (new_x < 1 || new_x > GAME_WIDTH || new_y < 1 || new_y > GAME_HEIGHT-1) {
        state->game_over = 1;
        state->death_reason = "Hit a wall!";
        return;
    }
    
    // Self collision
    SnakeNode* curr = state->head;
    while(curr) {
        if(curr->x == new_x && curr->y == new_y) {
            state->game_over = 1;
            state->death_reason = "Bit your own tail!";
            return;
        }
        curr = curr->next;
    }
    
    // Check food hit
    int ate_food = (new_x == state->food_x && new_y == state->food_y);
    
    // Allocate new head node
    SnakeNode* new_head = (SnakeNode*)alloc(sizeof(SnakeNode));
    new_head->x = new_x;
    new_head->y = new_y;
    new_head->next = state->head;
    state->head = new_head;
    
    if (ate_food) {
        state->score += 10;
        spawn_food(state);
        // Do not remove tail - snake grows
    } else {
        // Remove tail
        SnakeNode* temp = state->head;
        while(temp->next && temp->next->next) {
            temp = temp->next;
        }
        dealloc(temp->next);
        temp->next = 0;
        state->tail = temp;
    }
}

void render_game(GameState* state) {
    clear_screen();
    
    // Render score info
    move_cursor(BOARD_X_OFFSET, BOARD_Y_OFFSET - 1);
    char score_str[32];
    int_to_str(state->score, score_str);
    draw_string("Score: ");
    draw_string(score_str);
    
    // Draw top border
    move_cursor(BOARD_X_OFFSET, BOARD_Y_OFFSET);
    for(int x = 0; x <= GAME_WIDTH + 1; x++) draw_char('_');
    
    // Draw sides and contents
    for (int y = 1; y <= GAME_HEIGHT; y++) {
        move_cursor(BOARD_X_OFFSET, BOARD_Y_OFFSET + y);
        draw_char('|'); // Left wall
        
        move_cursor(BOARD_X_OFFSET + GAME_WIDTH + 1, BOARD_Y_OFFSET + y);
        draw_char('|'); // Right wall
    }
    
    // Draw bottom border
    move_cursor(BOARD_X_OFFSET, BOARD_Y_OFFSET + GAME_HEIGHT + 1);
    for(int x = 0; x <= GAME_WIDTH + 1; x++) draw_char('-');
    
    // Draw Food
    move_cursor(BOARD_X_OFFSET + state->food_x, BOARD_Y_OFFSET + state->food_y);
    draw_char('+');
    
    // Draw Snake
    SnakeNode* curr = state->head;
    while(curr) {
        move_cursor(BOARD_X_OFFSET + curr->x, BOARD_Y_OFFSET + curr->y);
        draw_char('O');
        curr = curr->next;
    }
    
    if (state->game_over) {
        move_cursor(BOARD_X_OFFSET + (GAME_WIDTH / 2) - 5, BOARD_Y_OFFSET + (GAME_HEIGHT / 2));
        draw_string("GAME OVER!");
    }
    
    move_cursor(1, BOARD_Y_OFFSET + GAME_HEIGHT + 3);
}
