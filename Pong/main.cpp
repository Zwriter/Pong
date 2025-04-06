#include <iostream>
#include "Game.h"

// using namespace sf;

int main()
{
    /// Init Game engine || Game render

    srand(static_cast<unsigned>(time(0)));

    Game game; 

    /// Event Polling

    while (game.isRunning())
    {
        // Update
        game.update();
        // Render
        game.render();
    }

    return 0;
}