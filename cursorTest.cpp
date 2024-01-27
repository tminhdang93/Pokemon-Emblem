#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Map.h"
//test for rendering and moving a cursor around the board. 

int main(){
    sf::RenderWindow window(sf::VideoMode(1900, 1200), "Curse was the only Pokemon move with the type ??? until 5th gen when it became Ghost-type", sf::Style::Close);
    Map testMap;
    sf::Vector2i position = sf::Mouse::getPosition(window);
    //testMap.getTile(0, 1).getPokemon().printStats();
    //testMap.getTile(0, 2).getPokemon().printStats();
    int count =0;
    
    //testing if map renders
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if(event.type == sf::Event::KeyReleased){
                
                switch(event.key.code){
                    case sf::Keyboard::Up:
                    testMap.cursorUp(); // just fixed names and stuff and works fine
                    break;
                    case sf::Keyboard::Down:
                    testMap.cursorDown();
                    break;
                    case sf::Keyboard::Left:
                    testMap.cursorLeft();
                    break;
                    case sf::Keyboard::Right:
                    testMap.cursorRight();
                    break;
                    case sf::Keyboard::Z:
                    ;
                }

                if(testMap.getTile(testMap.cursorX/150, testMap.cursorY/150).getPokemon().getID() > 0){
                    testMap.getTile((testMap.cursorX/150), (testMap.cursorY/150)).getPokemon().printStats();
                } //this goes here TT
            }
        }
        
        window.clear();
        //test if map renders (and if assigning the map sprite to tiles instead of map works).
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                window.draw(testMap.getTile(i, j).getTileSprite());
                if(testMap.getTile(i, j).getPokemon().getID() > 0 && testMap.getTile(i, j).getPokemon().getID() < 7){
                    window.draw(testMap.getTile(i, j).getPokemon().getSprite(i, j));
                }
            }
        }
        //test if map renders cursor
        window.draw(testMap.getCursor());
        window.display();
    }

}