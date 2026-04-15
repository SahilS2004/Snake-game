# Standardized Snake Engine 🐍

A robust, intricately structured implementation of the timeless Snake game, written from scratch in low-level **C** with custom OS-level handlers, alongside a dedicated **Web-Based UI** port.

This project is designed as an educational and technical showcase, emphasizing raw system manipulation, memory mechanics, linked lists, and non-blocking I/O over high-level standard libraries.

---

## 📂 Project Directory Structure

The codebase is split into specific, modular subsystems, avoiding "spaghetti code" by cleanly isolating concerns. Let's look at what each component does:

```text
Snake-game/
├── README.md         # You are here! Complete documentation & execution guide.
├── Makefile          # 🛠️ Build script to automate compilation.
│
├── bin/
│   └── snake         # 📦 The pre-compiled UNIX executable binary.
│
├── web/
│   └── index.html    # 🌐 The entirely self-contained HTML5/JS Web port of the game.
│
├── src/              # C Source Files
│   ├── main.c        # The application's entry point and lifecycle orchestrator.
│   ├── game.c        # Core game logic: movement, collisions, and state tracking.
│   ├── keyboard.c    # OS-level terminal configuration.
│   ├── screen.c      # ANSI Escape character functions to manually draw pixels.
│   ├── math.c        # Contains `random_range` and lightweight math utilities.
│   ├── memory.c      # A handcrafted block allocator managing heap memory.
│   └── string.c      # String implementations avoiding `#include <stdio.h>` limits.
│
└── include/          # C Header Definitions
    ├── game.h
    ├── keyboard.h
    ├── math.h
    ├── memory.h
    ├── screen.h
    └── string.h
```

---

## ⚙️ Core Technical Flow (C Implementation)

### 1. Initialization (`init_game` & `init_keyboard`)
When you launch the game via `main.c`, the execution jumps straight into setup protocols. 
1. **Memory Booting**: The game triggers `init_memory()`, reserving space for game nodes manually without calling standard `malloc` dynamically everywhere. 
2. **State Construction**: `init_game()` builds the initial `GameState`, generating the `SnakeNode` linked list that starts at the center. 
3. **Terminal Takeover**: `init_keyboard()` executes, engaging UNIX `termios.h`. By turning off `ICANON` and `ECHO`, the terminal stops buffering input (waiting for you to hit Enter). `fcntl` is also configured to set STDIN to `O_NONBLOCK`, allowing the game loop to spin freely instead of freezing while waiting for a key stroke.

### 2. The Real-Time Loop
The `while(!state.game_over)` loop runs indefinitely, paced by `usleep(100000)`—yielding exactly a 100-millisecond frame delay. Each tick follows a strict pipeline:

1. **Poll Input (`keyPressed`)**: Scans `STDIN_FILENO` aggressively for an arrow key (ansi `\033[` escapes) or W/A/S/D mapping.
2. **Update Vectors (`update_game`)**: 
    - The physics tick occurs. A new geometric head coordinate is calculated based on the current Direction vector (`UP`, `DOWN`, `LEFT`, `RIGHT`).
    - *Wall Checking:* Verifies the new coordinate against the static `GAME_WIDTH` (40) and `GAME_HEIGHT` (20) constants.
    - *Cannibal Checking:* Loops over the snake body linked list to ensure the head hasn't touched any existing coordinate.
3. **Allocation / Consumption**:
    - A new struct head is `alloc`'d to represent the physical move forward.
    - If `food` is at this new axis, the tail is **left alone**, naturally elongating the body and triggering a new `spawn_food()` recalculation.
    - If no food is eaten, the physical list `tail` is `dealloc`'d, maintaining the illusion of movement.
4. **Drawing (`render_game`)**: A `clear_screen()` wipe is fired, sending `\033[2J\033[H` ANSI bytes into stdout, rapidly painting the walls, body elements (`O`), and payload map before the next 100ms trigger occurs.

### 3. Graceful Termination (`reset_keyboard`)
Once `state->game_over` triggers to `1`, the while-loop releases. It is paramount that `reset_keyboard()` runs, utilizing `tcsetattr` to revert the user's terminal to canonical behaviors. If this step fails, the user's CLI session would remain broken, hidden, and unresponsive after execution.

---

## 🌐 The HTML5 Web Port Structure

The `index.html` file provides a 1:1 functional reflection of the C game logic via JavaScript, completely discarding the complex terminal environment constraints. 

### Web Flow:
- **Canvas Container**: Replaces the terminal's raw `screen.c` rendering, drawing to a strict 800x400 `<canvas>`.
- **Interval Timing**: the `usleep()` blocking architecture is swapped for JS's asynchronous `setInterval(gameLoop, 100)` handler.
- **Classic UI**: The DOM utilizes purely simple shapes (fillRect) and monospace fonts, mirroring an early pre-smartphone LCD aesthetic. Eyes dynamically shift perspective based on input vector tracking matching the `GameState` logic from C.

---

## 🚀 How to Compile and Play (Terminal)

Because this C implementation handles virtually all logical functionality internally without massive standard library bloat, compilation is incredibly simple.

If you are working from the project root, simply build the source code utilizing the provided `Makefile`:
```bash
make
```
Then execute:
```bash
./bin/snake
```
Or, you can compile and run it in a single command using:
```bash
make run
```
*(Press `Q` to instantly break execution and quit safely.)*

## 🎮 How to Play (Web)
For the modern Web edition, no compilation is required. 
Double-click `web/index.html` to open it in Chrome, Safari, Firefox, or any Chromium architecture browser. Click **START** and play using W/A/S/D or standard Arrow keys.
