#include "Game.h"

int main() {
    srand(time(NULL));
    Game game;
    while (!game.resume()) {
        game.update();
        game.render();
    }
}
