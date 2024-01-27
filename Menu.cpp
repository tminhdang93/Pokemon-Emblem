#include <iostream>
#include "Menu.h"

// Creating menu
Menu::Menu(float width, float height, int maxItems){
    menuWidth = width;
    menuHeight = height;
    maxMenuItems = maxItems;
}

Menu::Menu(){
    menuWidth = 0;
    menuHeight = 0;
    maxMenuItems = 0;
}

Menu::~Menu(){

}

//Creating main menu
MainMenu::MainMenu(){
    menuWidth = 0;
    menuHeight = 0;
    maxMenuItems = 0;  

}
MainMenu::MainMenu(float width, float height, int maxItems)
    :Menu(width, height, maxItems){
    menuWidth = width;
    menuHeight = height;
    maxMenuItems = maxItems;  

}

//Establishing the menu
void MainMenu::establishMenu(){
    if(!font.loadFromFile("files/ChicagoFLF.ttf")){
        std::cout << "cannot find font" <<std::endl;
    }
    menuItem[0].setFont(font);
    menuItem[0].setFillColor(sf::Color::Red);
    menuItem[0].setString("New Game");
    menuItem[0].setPosition(sf::Vector2f(1300 + (menuWidth)/4, menuHeight/(maxMenuItems + 1) * 1));

    menuItem[1].setFont(font);
    menuItem[1].setFillColor(sf::Color::White);
    menuItem[1].setString("Load Game");
    menuItem[1].setPosition(sf::Vector2f(1300 + (menuWidth)/4, menuHeight/(maxMenuItems + 1) * 1.5));

    menuItem[2].setFont(font);
    menuItem[2].setFillColor(sf::Color::White);
    menuItem[2].setString("How to Play");
    menuItem[2].setPosition(sf::Vector2f(1300 + (menuWidth)/4, menuHeight/(maxMenuItems + 1)* 2));

    menuItem[3].setFont(font);
    menuItem[3].setFillColor(sf::Color::White);
    menuItem[3].setString("Exit");
    menuItem[3].setPosition(sf::Vector2f(1300 + (menuWidth)/4, menuHeight/(maxMenuItems + 1) * 2.5));
    selectedItemIndex = 0;
}

// return what item we are on
int Menu::getPressedIten(){
    return selectedItemIndex;
}

// draw the item
void MainMenu::drawMenu(sf::RenderWindow &window){
    for (int i = 0; i < maxMenuItems; i++){
            window.draw(menuItem[i]);
        }
}

// moves
void MainMenu::moveDown(){
    if(selectedItemIndex + 1 < maxMenuItems){
        menuItem[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItem[selectedItemIndex].setFillColor(sf::Color::Red);
        std::cout << "On menu item " << selectedItemIndex << "." << std::endl;
    }
}
void MainMenu::moveUp(){
    if(selectedItemIndex - 1 >= 0){
        menuItem[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItem[selectedItemIndex].setFillColor(sf::Color::Red);
        std::cout << "On menu item " << selectedItemIndex << "." << std::endl;
    }
}

MainMenu::~MainMenu(){

}

