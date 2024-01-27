#ifndef TILE_H
#define TILE_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "PokemonBase.h"
//class for establishing tiles, each tile represents a spot on the map and can hold a pokemon
class Tile{
    private:
    // For tiles and map
    sf::Texture mapImage;
    sf::Sprite spriteTile;
    PokemonBase pokemon; //Every tile can store a pokemon
    int tileSize; //for segmenting the screen and map
    public:
    // for tile coords
    int x; 
    int y;
    bool isEmpty; //if tile is empty
    Tile();
    Tile(int xCoord, int yCoord, PokemonBase anyPokemon); //creating tile
    //get the coordinates of the tile
    int getX();
    int getY();
    bool player1Checker(); //checks if pokemon on tile is of p1 or p2
    //get and set elements of the tile
    void setPokemon(PokemonBase anyPokemon); 
    PokemonBase getPokemon();
    void setTileSprite(int xCoord, int yCoord);
    sf::Sprite getTileSprite();
    PokemonBase findNearPokemon();
    ~Tile();
};
#endif //TILE_H