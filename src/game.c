// #include <conio.h> Для getch() (Windows)
// Для Linux можно использовать 

#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h> // или #include <unistd.h>
#include <unistd.h>
#include <time.h>

#define BRIGHT_RED    "\033[91m"
#define BRIGHT_GREEN  "\033[92m"
#define RESET         "\033[0m"

// Глобальные переменные игры

Player player;
Target target;
bool game_running;
bool hit;

void init_game() {
    player.x = MAP_WIDTH / 2;
    player.y = MAP_HEIGHT / 2;
    target.x = rand() % 50;
    target.y = rand() % 20;
    game_running = true;
    hit = false;
}

void update_game() {
    // Обработка ввода
    char ch;
    
    // Инициализация генератора текущим временем
    srand(time(NULL));
        
    initscr();
    cbreak();
    noecho();
    timeout(-1);
    ch = getch();
    if (ch != ERR) {
	    switch(ch) {
	        case 'w' : player.y--; hit = false; break;
	        case 's' : player.y++; hit = false; break;
	        case 'a' : player.x--; hit = false; break;
	        case 'd' : player.x++; hit = false; break;
	        case 'q' : game_running = false; break;
            case 'f' : hit = true; break;
	    }

	// Проверка границ
	    if (player.x < 0) player.x = 0;
	    if (player.x >= MAP_WIDTH) player.x = MAP_WIDTH - 1;
	    if (player.y < 0) player.y = 0;
	    if (player.y >= MAP_HEIGHT) player.y = MAP_HEIGHT - 1;
        if ((player.x == target.x) && (player.y == target.y)) game_running = false;
    }
    
    endwin();
    
}

void render_game() {
    system("clear");
    
    // Верхняя граница
    for (int x = 0; x < MAP_WIDTH + 2; x++) printf("#");
    printf("\n");
    
    // Поле с боковыми границами
    for (int y = 0; y < MAP_HEIGHT; y++) {
        printf("#"); // левая граница
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (x == player.x && y == player.y) {
                    printf("@");                
            } else if (x == target.x && y == target.y) {
                if ( ((x == player.x) == (x == target.x)) || ((y == player.y) == (y == target.y)) ) {
                    if(hit) {
                        target.x = rand() % 50;
                        target.y = rand() % 20;                        
                        printf(BRIGHT_RED "*" RESET);                        
                    } else {                    
                        printf(BRIGHT_GREEN "0" RESET);
                    }
                } else {
                    
                    printf(BRIGHT_GREEN "0" RESET);
                }
                                
            } else {
                printf(" ");
            }
        }
        printf("#\n"); // правая граница
    }
    
    // Нижняя граница
    for (int x = 0; x < MAP_WIDTH + 2; x++) printf("#");
    printf("\n");
    
    printf("Controls: WASD to move, Q to quit\n");
}

bool is_game_running() {
    return game_running;
}
