#include <unistd.h>
#include "game.h"
#include "highscore.h"
#include "keyboard.h"
#include "screen.h"
#include "string.h"

/**
 * Main application entry point.
 * Coordinates system initialization, the real-time game loop,
 * and graceful termination.
 */

int main(void) {
    GameState state;
    
    // 1. Initialize core systems
    init_game(&state);    // This calls init_memory and init_rand internally
    init_keyboard();      // Setup non-blocking, raw input
    
    // 2. Real-time game loop
    while (!state.game_over) {
        // A. Read user input
        char ch = keyPressed();
        
        // B. Logic: Check for exit key (Q)
        if (ch == 'q' || ch == 'Q') {
            break;
        }
        
        // C. Update game state
        update_game(&state, ch);
        
        // D. Render new frame
        render_game(&state);
        
        // E. Control speed (smooth gameplay)
        // 100,000 microseconds = 100ms delay per frame
        usleep(200000);
    }
    
    // 3. Persist high score to disk
    save_highscore(state.score);
    
    // 4. Graceful Exit
    // Restore original terminal behavior (ICANON/ECHO)
    reset_keyboard();
    
    // Use newlines to push the board up and ensure a clean area for the final score
    draw_string("\n\n\n\n\n"); 
    draw_string("Final Score: ");
    char score_str[32];
    int_to_str(state.score, score_str);
    draw_string(score_str);
    
    draw_string("\n\rHigh Score:  ");
    char hi_str[32];
    int_to_str(state.high_score, hi_str);
    draw_string(hi_str);
    
    draw_string("\n\rDone.\n");
    
    return 0;
}
