# Snake Game: Ultimate Viva Preparation Guide 🎓

This comprehensive guide is your study material to ace your Viva examination. It entirely unpacks the architecture, every single file's purpose, the build tools we used, and a granular explanation of the underlying OS-level C code. 

---

## 1. Project Toolkit: The Build Process 🛠️
You must be able to explain how the code goes from text to a running game.

**Q. "What did you use to build this project?"**
> **A:** "I wrote the game purely in C. To convert it into a running application, I used the **GCC (GNU Compiler Collection)** compiler. To automate building all the different files into one, I used **GNU Make**."

### How GCC Works (The Compilation Flow):
1. **Preprocessing:** It takes all your `#include "..."` files and mathematically dumps their text into your `.c` files.
2. **Compilation:** It converts your C logic into lower-level Assembly instructions.
3. **Assembly:** It turns Assembly into binary Object files (`.o`).
4. **Linking:** It takes all the separate `.o` files (for your keyboard, memory, main, etc.) and pieces them together so they can reference each other, outputting the final executable binary `bin/snake`.

### How GNU Make Works:
Instead of manually typing `gcc -Iinclude src/main.c src/game.c ...` every time, we established a **Makefile**. When you just type `make` in terminal, Make reads the `Makefile`, detects that `src/*.c` needs to be compiled, explicitly applies the `-Iinclude` flag so the compiler knows where the `.h` header files are located, and safely drops the compiled output to `bin/snake`.

---

## 2. File Directory Breakdown

### 🧩 The "Include" Directory (`include/*.h`)
Header (`.h`) files are the "blueprints". They simply define `structs` (like `SnakeNode`) and provide function signatures (like `void update_game()`), but they don't contain the actual mechanical logic.

### ⚙️ The "Source" Directory (`src/*.c`)
The `.c` files contain the exact mechanical execution of the headers.

#### 🎮 The System Manager
1. **`main.c`**: The orchestrator. It calls the initialization functions and holds the `100ms` infinite `while` loop that forces the game to keep running automatically without waiting for user input.
2. **`game.c`**: Contains the core mathematics. It executes movement math, calculates boundary limits (`new_x < 0`), and tracks if the Snake collides with itself or eats food. 

#### 💻 Hardware Controllers
3. **`keyboard.c`**: Handles OS-level terminal modifications via UNIX `termios`. By bypassing terminal "Canonical mode", it reads W/A/S/D inputs directly from the user's keystroke.
4. **`screen.c`**: Utilizes ANSI Escape Codes (`\033[...]`) to write literal strings directly to coordinates on the terminal interface to simulate "pixels".

#### 🧰 Custom Core Libraries
*Instead of utilizing heavy C standards like `<stdlib.h>` or `<stdio.h>`, you built custom lightweight variants:*
5. **`math.c`**: Modulo math to generate pseudo-random coordinates to place the red "food" block randomly on the grid.
6. **`string.c`**: Instead of using heavy functions like `sprintf` to convert the player's integer score into characters, this iterates mathematical division (`n % 10`) to pull digits from integers and map them to `char` sequences by adding `+'0'` ASCII offsets.
7. **`memory.c`**: An entirely customized memory allocator designed to replace `malloc()` and `free()`.

---

## 3. Deep Code Breakdown

### A. The Custom Memory Allocator (`memory.c`)
Standard application development uses `malloc()`, which asks the computer's OS Kernel for RAM anywhere it can find it. In a fast game repeatedly allocating nodes, this is extremely slow and fragments RAM. 

**How yours works:**
```c
#define RAM_SIZE (1024 * 1024)
static char ram[RAM_SIZE];
```
* **Explanation:** When the game starts, it instantly claims a static `1MB` block of RAM as an array. It no longer needs to ask the OS kernel for help dynamically. 

```c
typedef struct MemoryBlock {
    int size;
    int is_free;
    struct MemoryBlock* next;
} MemoryBlock;
```
* **Explanation:** Every `alloc()` call (like when the snake gets bigger) splits up this 1MB block. It writes a struct header before the memory so it secretly remembers how big the chunk is, whether it's currently being used (`is_free = 0`), and what memory block is next to it! When `dealloc()` is called, it flips `is_free` to `1` so another part of the game can safely overwrite it without going back to the OS!

### B. Stripping Terminal Buffering (`keyboard.c`)

Normally, in `scanf()`, you hit a key and the Terminal waits for you to hit "Enter" (Return). That would make playing a real-time snake game impossible.

```c
new_termios.c_lflag &= ~(ICANON | ECHO);
fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
```
* **Explanation:** 
    * `ICANON`: Canonical mode buffers input. Using bitwise `~(NOT)` disables this, reading keypresses byte-by-byte instantly.
    * `ECHO`: Disables the letters appearing on your screen when you type, so pressing "W" doesn't ruin the game canvas art.
    * `O_NONBLOCK`: The standard UNIX `.read()` command checks if a key is hit. If no key is hit, it pauses your application and waits forever until you do hit one. `O_NONBLOCK` overrides this, causing `.read()` to immediately skip and return 0 if no finger is on the keyboard, letting the game continue moving!

### C. The Number-to-String Conversion (`string.c`)

If your game ends, it prints the Score. You can't draw `int 32` instantly. It has to be the characters `'3'` and `'2'`. 

```c
while (n != 0) {
    s[i++] = (n % 10) + '0';
    n /= 10;
}
```
* **Explanation:** You iterate the number, hitting it with the remainder modulo `% 10`. So `32 % 10` returns `2`. 
We add `'0'` onto `2` to shift it into its string ASCII table variant. We then run `n /= 10` (so `32 / 10 = 3`) and repeat. This manually translates raw computer memory values into characters humans can read!

### D. The Snake Linked List logic (`game.c`)

**Q. Why a Linked List over an Array?**
> **A:** When a snake moves, only the most front position, and most back position changes. The entire middle body is technically static. With an Array, moving the Snake one step requires sliding every single index back physically. With a Linked List (`SnakeNode->next`), we add a new Head pointer to the front, and drop the Tail pointer in the back. *O(N)* time complexly is solved instantly in *O(1)*.

---

## 4. Final Viva Study Advice
Use this document to prepare explicitly. You now know:
1. **The Infrastructure**: GCC built your C into binary instructions. 
2. **The Flow**: You manage memory purely natively out of a 1MB pool, capture input via raw UNIX terminal overrides, string manipulation is math-based ASCII sliding, and you manipulate strings to tell the cursor exactly what terminal coordinates to draw on.
3. **The Data Structure**: Your Snake utilizes structural Linked-Lists.
