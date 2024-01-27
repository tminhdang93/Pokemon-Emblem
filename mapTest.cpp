#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Map.h"

int main(){
    //Testing if creating the window and map works
    sf::RenderWindow window(sf::VideoMode(2000, 1500), "Quick! Ina and Gura of UMISEA are missing. Use a 'MAP' to locate them.");
    Map testMap;
    sf::Vector2i position = sf::Mouse::getPosition(window);
    //testing if map renders
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();
        //test if map renders (and if assigning the map sprite to tiles instead of map works).
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                window.draw(testMap.getTile(i, j).getTileSprite());
                if(testMap.getTile(i, j).getPokemon().getID() != 0){
                    window.draw(testMap.getTile(i, j).getPokemon().getSprite(i, j));
                }
            }
        }
        window.display();
    }

}