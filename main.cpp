#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Dungeon MAN");

    Game game;
    game.Begin(window);

    return 0;
}
