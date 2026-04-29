CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -I$(INCDIR)
TARGET  = $(BINDIR)/snake

SRCDIR  = src
INCDIR  = include
BINDIR  = bin

SRCS    = $(wildcard $(SRCDIR)/*.c)
OBJS    = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS) | $(BINDIR)
	$(CC) $(OBJS) -o $(TARGET)

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
