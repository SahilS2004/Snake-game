CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = snake
SRCS = main.c game.c keyboard.c math.c memory.c screen.c string.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
