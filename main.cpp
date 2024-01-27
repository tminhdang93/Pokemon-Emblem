#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Game.h"

int main()
{
    //initialise game engine
    Game game;
    //game running - continuous check
    while (game.running()){
        //Update
        game.update();
        //Render
        game.render();
    }
return 0;
}