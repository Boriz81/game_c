CC = gcc
CFLAGS = -Wall -Wextra
TARGET = my_game
SRC = src/main.c src/game.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
