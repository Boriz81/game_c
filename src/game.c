#include "game.h"
#include <stdio.h>
#include <stdlib.h>
// #include <conio.h> // Для getch() (Windows)

// Для Linux можно использовать 
#include <ncurses.h> // или #include <unistd.h>
#include <unistd.h>
// Глобальные переменные игры
Player player;
bool game_running;

void init_game() {
    player.x = MAP_WIDTH / 2;
    player.y = MAP_HEIGHT / 2;
    game_running = true;
}

void update_game() {
    // Обработка ввода
    char ch;
    initscr();
    cbreak();
    noecho();
    timeout(-1);
    ch = getch();
    if (ch != ERR) {
	switch(ch) {
	    case 'w' : player.y--; break;
	    case 's' : player.y++; break;
	    case 'a' : player.x--; break;
	    case 'd' : player.x++; break;
	    case 'q' : game_running = false; break;
	}

	// Проверка границ
	if (player.x < 0) player.x = 0;
	if (player.x >= MAP_WIDTH) player.x = MAP_WIDTH - 1;
	if (player.y < 0) player.y = 0;
	if (player.y >= MAP_HEIGHT) player.y = MAP_HEIGHT - 1;
    }
    endwin();
}

void render_game() {
    system("clear"); // Очистка экрана (Linux)
    // Для виндовс system("cls")
    
    // Рендеринг карты
    for (int y = 0; y < MAP_HEIGHT; y++) {
	for (int x = 0; x < MAP_WIDTH; x++) {
	    if (x == player.x && y == player.y) {
		printf("@"); //игрок
	    } else {
	        printf(".");
	    }
	}
	printf("\n");
    }

    printf("Controls: WASD to move, Q to quit\n");
}

bool is_game_running() {
    return game_running;
}
