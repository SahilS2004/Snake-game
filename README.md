# 🐍 C-Snake: Low-Level Terminal Game

A performance-optimized Snake game written in C that demonstrates core systems programming concepts. Unlike standard implementations, this project avoids most standard library overhead by implementing custom memory management, terminal rendering, and non-blocking input handling.

![Snake Game Demo](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Terminal-Based](https://img.shields.io/badge/Terminal-UI-4E9A06?style=for-the-badge&logo=gnumetadata&logoColor=white)

## 🚀 Key Technical Features

- **Custom Memory Management**: Implements a Linked-List based Free-List allocator with block splitting and coalescing to manage a static 1MB heap.
- **ANSI Rendering Engine**: Uses raw ANSI escape sequences for flicker-free terminal manipulation without external dependencies like `ncurses`.
- **Non-Blocking I/O**: Configures the terminal's `termios` flags to capture immediate keypresses without requiring the `Enter` key.
- **Standard Library Replacements**: Includes custom implementations for string manipulation, math operations, and random number generation.

## 🛠️ Installation & Build

Ensure you have a C compiler (`gcc` or `clang`) installed.

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/snake-game.git
   cd snake-game/Snake-game
   ```

2. **Compile the project**:
   Using the provided Makefile:
   ```bash
   make
   ```
   Or manually:
   ```bash
   gcc main.c game.c keyboard.c math.c memory.c screen.c string.c -o snake
   ```

3. **Run the game**:
   ```bash
   ./snake
   ```

## 🎮 Controls

- **W**: Move Up
- **S**: Move Down
- **A**: Move Left
- **D**: Move Right
- **Q**: Quit Game

## 📂 Project Structure

| File | Description |
| :--- | :--- |
| `main.c` | Entry point and the real-time game loop. |
| `game.c/h` | Core game logic, collision detection, and score management. |
| `memory.c/h` | Custom memory allocator (linked-list on static buffer). |
| `keyboard.c/h` | Terminal configuration for raw, non-blocking input. |
| `screen.c/h` | Rendering engine using ANSI escape codes. |
| `string.c/h` | Custom string handling and integer-to-string conversion. |
| `math.c/h` | Custom math functions and pseudo-random number generation. |

## 🧠 Architectural Overview

### 1. Memory Management
The game uses a global array `ram[1024 * 1024]` to simulate physical memory. The `alloc()` function implements a **First-Fit** strategy, splitting blocks when necessary. The `dealloc()` function performs **Coalescing**, merging adjacent free blocks to mitigate fragmentation.

### 2. Terminal Logic
By setting the terminal to **Non-Canonical Mode** using `termios`, the application can read input bytes immediately. The UI is updated by sending specific byte sequences like `\033[H` (cursor home) to the terminal, allowing for high-speed rendering.

---

Developed as a demonstration of low-level C programming.
