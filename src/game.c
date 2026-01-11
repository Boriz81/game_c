// #include <conio.h> Для getch() (Windows)
// Для Linux можно использовать

#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h> // или #include <unistd.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define BRIGHT_BLACK    "\033[90m"
#define BRIGHT_RED      "\033[91m"
#define BRIGHT_GREEN    "\033[92m"
#define BRIGHT_YELLOW   "\033[93m"
#define BRIGHT_BLUE     "\033[94m"
#define BRIGHT_MAGENTA  "\033[95m"
#define BRIGHT_CYAN     "\033[96m"
#define BRIGHT_WHITE    "\033[97m"
#define RESET           "\033[0m"

// Глобальные переменные игры
int start;
// char[333] name;

void timer_start(Timer *timer) {
    timer->start_time = time(NULL);
}

double timer_get_elapsed(Timer *timer) {
    timer->elapsed_seconds = difftime(time(NULL),timer->start_time);
    return timer->elapsed_seconds;
}

int timer_is_time_up(Timer *timer, double limit_seconds) {
    return timer_get_elapsed(timer) >= limit_seconds;
}

void start_game() {
    
                
    init_game();

    Timer game_timer;
    timer_start(&game_timer);
        
    while (is_game_running()) {

        double elapsed = timer_get_elapsed(&game_timer);
        printf("Time: %.2f seconds\n", elapsed);

        if (timer_is_time_up(&game_timer, 60.0)) {
            printf("Time's up!\n");
            break;
        }

        update_game();
	    render_game();
    }
    
}

Player player;
Target target;
bool game_running;
bool hit;
int count;

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
    
    int *ptr = &count;
    
    // Верхняя граница
    for (int x = 0; x < MAP_WIDTH + 2; x++) printf("#");
    printf("\n");
    
    // Поле с боковыми границами
    for (int y = 0; y < MAP_HEIGHT; y++) {
        printf("#"); // левая граница
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (x == player.x && y == player.y) {
                if (count >= 5) {
                    printf(BRIGHT_BLUE "@" RESET);
                } else { printf(RESET "@"); }
            } else if (x == target.x && y == target.y) {
                if ( ((x == player.x) == (x == target.x)) || ((y == player.y) == (y == target.y)) ) {
                    if(hit) {
                        target.x = rand() % 50;
                        target.y = rand() % 20;                        
                        printf(BRIGHT_RED "*" RESET);
                        (*ptr)++;                        
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

    printf("Hit: %d\n", count);    

    printf("Controls: WASD to move, Q to quit\n");
}

bool is_game_running() {
    return game_running;
}
// Хэширование пароля (простейшее)
unsigned int simpleHash(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + *str;
        str++;
    }
    return hash;
}

void saveUser(User user) {
    FILE *file = fopen("users.dat", "ab");
    if (file) {
        // Сохраняем хэш пароля, а не сам пароль
        unsigned int passHash = simpleHash(user.password);
        fwrite(&user.username, sizeof(user.username), 1, file);
        fwrite(&passHash, sizeof(passHash), 1, file);
        fwrite(&user.highScore, sizeof(user.highScore), 1, file);
        fwrite(&user.gamePlayed, sizeof(user.gamePlayed), 1, file);
        fclose(file);
    }
}

int findUser(const char *username, User *foundUser) {
    FILE *file = fopen("users.dat", "rb");
    if (!file) return 0;

    User temp;
    unsigned int storedHash;

    while (fread(&temp.username, sizeof(temp.username), 1, file)) {
        fread(&storedHash, sizeof(storedHash), 1, file);
        fread(&temp.highScore, sizeof(temp.highScore), 1, file);
        fread(&temp.gamePlayed, sizeof(temp.gamePlayed), 1, file);

        if (strcmp(temp.username, username) == 0) {
            *foundUser = temp;
            // Сохраняем хэш как "пароль" для проверки
            sprintf(foundUser->password, "%u", storedHash);
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void registerUser() {
    User newUser;

    printf("=== РУГИСТРАЦИЯ ===\n");
    printf("Придумайте логин: ");
    scanf("%49s", newUser.username);

    // Проверка существования

    User existing;
    if (findUser(newUser.username, &existing)) {
        printf("Пользователь уже существует!\n");
        return;
    }

    printf("Придумайте пароль: ");
    scanf("%49s", newUser.password);

    newUser.highScore = 0;
    newUser.gamePlayed = 0;

    saveUser(newUser);
    printf("Регистрация успешна!\n");
}

int loginUser(User *loggedUser) {
    char username[50];
    char password[50];

    printf("=== ВХОД ===\n");
    printf("Логин: ");
    scanf("%49s", username);

    printf("Пароль: ");
    scanf("%49s", password);

    User found;
    if (findUser(username, &found)) {
        // Проверяем хэш пароля
        unsigned int inputHash = simpleHash(password);
        unsigned int storedHash = atoi(found.password);

        if (inputHash == storedHash) {
            *loggedUser = found;
            strcpy(loggedUser->username, username);
            printf("Вход выполнен! Ваш рекорд: %d\n", found.highScore);
            return 1;
        }
    }

    printf("Неверный логин или пароль!\n");
    return 0;
}

// void updateScore(const char *username, int newScore) {}

void showMenu() {
    printf("\n === MENU ===\n");
    printf("1. Enter\n");
    printf("2. Zaregatsy\n");
    printf("3. Sign Out\n");
    printf("Choise: ");
}