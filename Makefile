CFLAGS = -Wall -Wextra
LIBS = -lncurses
CC = gcc


my_game: src/main.c src/game.c
	$(CC) $(CFLAGS) -o my_game src/main.c src/game.c $(LIBS)


clean:
	rm -f my_game
