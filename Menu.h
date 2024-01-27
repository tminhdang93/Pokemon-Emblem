#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
/**
 * Menu class which creates the menus on the game interface
 */
class Menu{
    protected:
    int maxMenuItems; //maximum number of menu items
    float menuWidth; //calculates the x-position of the menu items
    float menuHeight; //used to calculate the y-position of the menu items
    int selectedItemIndex; //what item we are on
    //sf::Text *menuItem; 
    sf::Font font;
    public:
    Menu(float width, float height, int maxMenuItems); //create menu
    virtual void establishMenu() = 0; //create a menu - each menu has different properties
    // for moving
    void moveDown();
    void moveUp();
    Menu();
    int getPressedIten(); //return what item we are on
    void drawMenu(sf::RenderWindow &window); //draw the menu onto the game window
    ~Menu();
};
class MainMenu: public Menu{
    private:
    sf::Text menuItem[4]; //items have text
    public:
    //creating main menu
    MainMenu();
    MainMenu(float width, float height, int maxMenuItems); 
    void establishMenu();
    void drawMenu(sf::RenderWindow &window); //draw the menu onto the game window
    //For moves
    void moveDown();
    void moveUp();
    ~MainMenu();
};

#endif //MENU_H