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
   git clone https://github.com/SahilS2004/Snake-game.git
   cd Snake-game
   ```

2. **Compile the project**:
   ```bash
   make
   ```

3. **Run the game**:
   ```bash
   ./bin/snake
   ```

4. **Clean build artifacts**:
   ```bash
   make clean
   ```

## 🎮 Controls

- **W / ↑**: Move Up
- **S / ↓**: Move Down
- **A / ←**: Move Left
- **D / →**: Move Right
- **Q**: Quit Game

## 📂 Project Structure

```
Snake-game/
├── include/            # Header files (.h)
│   ├── game.h          # Game state, types, and logic declarations
│   ├── keyboard.h      # Non-blocking input interface
│   ├── math.h          # Custom math & PRNG declarations
│   ├── memory.h        # Custom memory allocator interface
│   ├── screen.h        # ANSI rendering interface
│   └── string.h        # Custom string utility declarations
│
├── src/                # Source files (.c)
│   ├── main.c          # Entry point and real-time game loop
│   ├── game.c          # Core game logic, collision, scoring
│   ├── keyboard.c      # Terminal raw-mode & input handling
│   ├── math.c          # Bitwise math & pseudo-random generator
│   ├── memory.c        # Linked-list heap allocator on static buffer
│   ├── screen.c        # ANSI escape-code renderer
│   └── string.c        # String manipulation & int-to-string
│
├── web/                # Browser-based version
│   └── index.html      # Canvas-based Snake (retro edition)
│
├── docs/               # Documentation & reports
│   ├── report.tex      # IEEE-format LaTeX source
│   └── report.pdf      # Compiled paper
│
├── bin/                # Compiled binary output (git-ignored)
├── Makefile            # Automated build system
├── .gitignore          # Build artifacts & OS files exclusion
└── README.md           # This file
```

## 🧠 Architectural Overview

### 1. Memory Management
The game uses a global array `ram[1024 * 1024]` to simulate physical memory. The `alloc()` function implements a **First-Fit** strategy, splitting blocks when necessary. The `dealloc()` function performs **Coalescing**, merging adjacent free blocks to mitigate fragmentation.

### 2. Terminal Rendering
By sending specific ANSI escape sequences like `\033[H` (cursor home) and `\033[2J` (clear screen), the engine achieves flicker-free rendering without any external UI library dependency.

### 3. Input Handling
By setting the terminal to **Non-Canonical Mode** using `termios`, the application reads input bytes immediately. Arrow keys are decoded from their multi-byte ANSI escape sequences and mapped to WASD equivalents.

### 4. Math & PRNG
All math operations (multiply, divide, modulo, absolute value) are implemented from scratch using **bitwise shift-and-add** algorithms. The pseudo-random number generator uses a **Linear Congruential Generator** seeded at game start.

---

Developed as a demonstration of low-level C programming.
