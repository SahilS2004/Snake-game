CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/game.c src/keyboard.c src/math.c src/memory.c src/screen.c src/string.c
OUT = bin/snake

all: $(OUT)

$(OUT): $(SRC)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -rf bin/
