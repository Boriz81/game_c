#include "game.h"
#include <stdio.h>

int main() {
    init_game();
    render_game();

    while (is_game_running()) {
	update_game();
	render_game();
    }

    printf("%s", "Game over!\n");
    return 0;
}
