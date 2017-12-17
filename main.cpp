#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Conway.h"

const int TPS = 60;

int main() {
    Game game(TPS);
    game.Run();

    return 0;
}
