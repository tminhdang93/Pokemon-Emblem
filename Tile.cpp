#include <iostream>
#include "Tile.h"
#include "Map.h"
//Functions are all explained in the .h file
Tile::Tile(){ //Empty tile
    this -> x = 0;
    this -> y = 0;
    setTileSprite(0,0);
}
// Creating a tile
Tile::Tile(int xCoord, int yCoord, PokemonBase p){
    this -> x = xCoord;
    this -> y = yCoord;
    this -> pokemon = p;
    setTileSprite(x, y);
    this -> pokemon.getSprite(x, y);
    if(this -> pokemon.getID() == 0){
        isEmpty = true; //checking if its empty
    }
}
//Return coords
int Tile::getX(){return this -> x;}
int Tile::getY(){return this -> y;}

//Setting pokemon to tile
void Tile::setPokemon(PokemonBase p){this -> pokemon = p;}

//Get pokemon on tile
PokemonBase Tile::getPokemon(){return this -> pokemon;}

//Setting sprite to tile
//Setting up map
void Tile::setTileSprite(int xCoord, int yCoord){
    this ->tileSize = 150;
    if (!this -> mapImage.loadFromFile("files/grid1.png")){
        std::cout << "cannot load tile [" << xCoord << "][" << yCoord << "]" << std::endl;
    }
    this -> spriteTile.setTexture(mapImage);
    this -> spriteTile.setTextureRect(sf::IntRect(xCoord * tileSize, yCoord * tileSize, tileSize, tileSize));
    this -> spriteTile.setPosition(xCoord * tileSize, yCoord * tileSize);
}

//Get sprite
sf::Sprite Tile::getTileSprite(){return this -> spriteTile;}

Tile::~Tile(){} //Deconstructor