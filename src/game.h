#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <time.h>

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
typedef struct {
    time_t start_time;
    double elapsed_seconds;
} Timer;

// Объявление функций

void menu_game();
void init_game();
void update_game();
void render_game();
bool is_game_running();
void timer_start();
double timer_get_start(Timer *timer);
int timer_is_time_up(Timer *timer, double limit_seconds);

#endif // GAME_H
