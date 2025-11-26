#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

// Определение констант
#define MAP_WIDTH 50
#define MAP_HEIGHT 20

// Объявление структур
typedef struct {
    int x;
    int y;
} Player;
typedef struct {
    int x;
    int y;
} Target;

// Объявление функций
void init_game();
void update_game();
void render_game();
bool is_game_running();

#endif // GAME_H
