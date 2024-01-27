#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Tile.h"
//class for establishing the map - the map is a 8x8 board which holds all the active Pokemon.
class Map{
    protected:
    //cursor which is used to select items on map
    sf::Texture cursorImage;
    sf::Sprite cursorSprite;
    
    int tileSize; //tile size - for proportioning
    public:
    Tile *tiles[8][8]; //tiles on the map
    PokemonBase enemyPoke; //Creates object 'enemyPoke' from class 'PokemonBase' for battle phase.
    PokemonBase allyPoke; //Creates object 'allyPoke' from class 'PokemonBase' for battle phase.
    int enemyPokeID; //Used to attach a corresponding pokemon stat block to 'enemyPoke'.
    int allyPokeID; //Used to attach a corresponding pokemon stat block to 'allyPoke'.
    int cursorX; //cursor position
    int cursorY;
    //Creates object <pokemon> and assigns it a corresponding subclass, which contains definite values for all data members except alignment.
    PokemonBase Bulb1; 
    PokemonBase Char1; 
    PokemonBase Squi1; 
    PokemonBase Turt1; 
    PokemonBase Torc1; 
    PokemonBase Osha1; 

    PokemonBase Bulb2; 
    PokemonBase Char2 ;
    PokemonBase Squi2 ;
    PokemonBase Turt2 ;
    PokemonBase Torc2 ;
    PokemonBase Osha2 ;

    PokemonBase temp; //Creating a temp variable to store Pokemon if needed
    
    Map(); //Runs createMap(), createCursor(), and sets tileSize.
    void createMap(); //create tiles as well as those with occupied pokemon
    void createCursor(); //create cursor
    sf::Sprite getCursor();
    //move cursor around
    void cursorUp();
    void cursorDown();
    void cursorLeft();
    void cursorRight();
    void moveCursor(sf::Event &ev);
    Tile getTile(int x, int y); //get the tile that we are on
    bool isPieceNearby(int file, int rank, bool player1turn); //file is X position, rank is Y position.
    //PokemonBase pieceFront(int x, int y, bool player1turn);
    PokemonBase getPBase(int ID); 
    ~Map();
};

#endif //MAP_H