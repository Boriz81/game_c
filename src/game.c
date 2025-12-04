#include "game.h"
#include <stdio.h>
#include <stdlib.h>
// #include <conio.h> // Для getch() (Windows)

// Для Linux можно использовать 
#include <ncurses.h> // или #include <unistd.h>
#include <unistd.h>
// Глобальные переменные игры
Player player;
Target target;
bool game_running;
bool fire_target;

void init_game() {
    player.x = MAP_WIDTH / 2;
    player.y = MAP_HEIGHT / 2;
    target.x = 2;
    target.y = 2;
    game_running = true;
    fire_target = true;
}

/*void fire_target(int x, int y) {
    if (player.x && player.y) {
        printf("----------");
    }    
}
*/


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
	        case 'w' : player.y--; fire_target = true; break;
	        case 's' : player.y++; fire_target = true; break;
	        case 'a' : player.x--; fire_target = true; break;
	        case 'd' : player.x++; fire_target = true; break;
	        case 'q' : game_running = false; break;

            case 'f' : fire_target = false; break;
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
                if(fire_target) {
                    printf("@"); 
                } else { 
                    printf("-");
                }
                
            } else if (x == target.x && y == target.y) {
                printf("0");
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
