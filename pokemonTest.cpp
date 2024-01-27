#include "PokemonBase.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <time.h>

//Checking if creating the pokemon works
int main(){
    //Creating window and Pokemon
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    PokemonBase Bulbasaur = PokemonBase(1, "Bulbasaur", 1, 49, 49, 45);
    PokemonBase Turtwig = PokemonBase(2, "Turtwig", 1, 68, 64, 55);
    PokemonBase Charmander = PokemonBase(3, "Charmander", 2, 52, 43, 39);
    PokemonBase Torchic = PokemonBase(4, "Torchic", 2, 60, 40, 45);
    PokemonBase Squirtle = PokemonBase(5, "Squirtle", 3, 48, 65, 44);
    PokemonBase Oshawott = PokemonBase(6, "Oshawott", 3, 55, 45, 55);
    PokemonBase pokemon = PokemonBase();
    //Trying other functions
    Charmander.printStats();
    Charmander.levelUp();
    Charmander.printStats();
    Charmander.levelUp();
    Charmander.printStats();
    Bulbasaur.printStats();
    Bulbasaur.levelUp();
    Bulbasaur.printStats();
    pokemon.printStats();
    Oshawott.gainEXP(30);
    Turtwig.gainEXP(100);
    Oshawott.gainEXP(50);
    Oshawott.gainEXP(30);
    //Changes to window
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(Charmander.getSprite(0,0));
        window.display();
    }

    return 0;
}