#include "game.h"
#include <stdio.h>

int main() {
    User currentUser;
    int loggedIn = 0;
    int choice;

    do {
        showMenu();
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                if (loginUser(&currentUser)) {
                    loggedIn = 1;
                    // Запуск игры
                    start_game(currentUser.username, &currentUser.highScore);
                }
                break;
            case 2:
                registerUser();
                break;
            case 3:
                printf("Выход...\n");
                break;
            default:
                printf("Неверный выбор!\n");
        }
    } while (choice != 3 && !loggedIn);
    
    
    

    printf("%s", "Game over!\n");
    return 0;
}
