#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

// Определение констант
#define MAP_WIDTH 20
#define MAP_HEIGHT 10

// Объявление структур
typedef struct {
    int x;
    int y;
} Player;

// Объявление функций
void init_game();
void update_game();
void render_game();
bool is_game_running();

#endif // GAME_H
