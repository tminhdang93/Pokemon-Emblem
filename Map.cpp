#include <iostream>
#include "Map.h"
#include "PokemonBase.h"


Map::Map(){
    createMap();
    createCursor();
    tileSize = 150; //tile size - for proportioning
}

void Map::createMap(){
    //Creating pokemon and setting up their moves
    Bulb1 = Bulbasaur(true); 
    Bulb1.moveset[2]->buffNo = 3;
    //std::cout <<"buff numb is "<<Bulb1.moveset[2]->buffNo << "\n";
    Char1 = Charmander(true);
    Char1.moveset[2]->buffNo = 3;
    Squi1 = Squirtle(true);
    Squi1.moveset[2]->buffNo = 4;
    Turt1 = Turtwig(true);
    Turt1.moveset[2]->buffNo = 2;
    Torc1 = Torchic(true);
    Torc1.moveset[2]->buffNo = 1;
    Osha1 = Oshawott(true);
    Osha1.moveset[2]->buffNo = 1;

    Bulb2 = Bulbasaur(false);
    Char2 = Charmander(false);
    Squi2 = Squirtle(false);
    Turt2 = Turtwig(false);
    Torc2 = Torchic(false);
    Osha2 = Oshawott(false);
    Bulb2.moveset[2]->buffNo = 3;
    Char2.moveset[2]->buffNo = 3;
    Squi2.moveset[2]->buffNo = 4;
    Turt2.moveset[2]->buffNo = 2;
    Torc2.moveset[2]->buffNo = 1;
    Osha2.moveset[2]->buffNo = 1;

    //Creates a 8x8 array of tiles, each containing an x coord, a y coord, and 'PokemonBase()'.
    for (int r = 0; r < 8; r++){
        for (int c = 0; c < 8; c++){
            tiles[r][c] = new Tile(r, c, PokemonBase()); //PokemonBase() sets the pokemon on the tile to null values.
        }
    }
    // Setting the pokemon each a player number
    Bulb1.playerNo = 1;
    Char1.playerNo = 1;
    Squi1.playerNo = 1;
    Turt1.playerNo = 1;
    Torc1.playerNo = 1;
    Osha1.playerNo = 1;

    Bulb2.playerNo = 2;
    Char2.playerNo = 2;
    Squi2.playerNo = 2;
    Turt2.playerNo = 2;
    Torc2.playerNo = 2;
    Osha2.playerNo = 2;
    //Setting up and creating the tiles
    tiles[0][1] = new Tile(0, 1, Bulb1);
    tiles[0][2] = new Tile(0, 2, Char1);
    tiles[0][3] = new Tile(0, 3, Squi1);
    tiles[0][4] = new Tile(0, 4, Turt1);
    tiles[0][5] = new Tile(0, 5, Torc1);
    tiles[0][6] = new Tile(0, 6, Osha1);

    tiles[7][1] = new Tile(7, 1, Bulb2);
    tiles[7][2] = new Tile(7, 2, Char2);
    tiles[7][3] = new Tile(7, 3, Squi2);
    tiles[7][4] = new Tile(7, 4, Turt2);
    tiles[7][5] = new Tile(7, 5, Torc2);
    tiles[7][6] = new Tile(7, 6, Osha2);
    
}

//Checking if there is a piece nearby, and if there is setting a temp variable enemypoke or allypoke to store the nearby pokemon
bool Map::isPieceNearby(int file, int rank, bool player1turn) {
            if (file > 0 && file < 7){
                for (int row = -1; row < 0; row++) { // it doesnt even need to be in a loop lmao but we can fix it later
                        //If it is player 2's turn, current pokemon on tile = p2 and isnt empty,, and the pokemon to the left belongs to player 1, get identity of pokemon.
                        
                        if (((tiles[file-1][rank])->getPokemon().playerNo) == 1 && player1turn == false ) {
                            enemyPokeID = ((tiles[file-1][rank]->getPokemon().getID())); // gets pokemon on tiles ID
                            // the enemypokemons id is found above, so if its p2 turn and the left pokemon of thr tile ur on is of player 1
                            // enemypokeid gets set to the enemy pokemons id, and depending on that enemypokemon the variable will get set to 
                            // the current pokemon of player 1 on the left of the tile that p2 is on and vice versa for the part below
                            //Inputs ID of pokemon, and assigns object 'enemyPoke' the predefined stats of the corresponding pokemon.
                            if (enemyPokeID == 1){enemyPoke = Bulb1;}
                            else if(enemyPokeID == 2){enemyPoke = Turt1;} 
                            else if(enemyPokeID == 5){enemyPoke = Squi1;}
                            else if(enemyPokeID == 3){enemyPoke = Char1;} 
                            else if(enemyPokeID == 4){enemyPoke = Torc1;}
                            else if(enemyPokeID == 6){enemyPoke = Osha1;} 
                            
                            allyPokeID = (tiles[file][rank]->getPokemon().getID());
                            if(allyPokeID==1){allyPoke=Bulb2;}
                            if(allyPokeID==2){allyPoke=Turt2;}
                            if(allyPokeID==3){allyPoke=Char2;}
                            if(allyPokeID==4){allyPoke=Torc2;}
                            if(allyPokeID==5){allyPoke=Squi2;}
                            if(allyPokeID==6){allyPoke=Osha2;}

                            return true;
                        } else if((tiles[file+1][rank]->getPokemon().playerNo == 2) && player1turn == true ){
                            // checks if a player 2 pokemon is on the right of p1
                            enemyPokeID = ((tiles[file+1][rank]->getPokemon().getID()));
                            if (enemyPokeID == 1){enemyPoke = Bulb2;}
                            else if(enemyPokeID == 2){enemyPoke = Turt2;} 
                            else if(enemyPokeID == 5){enemyPoke = Squi2;}
                            else if(enemyPokeID == 3){enemyPoke = Char2;} 
                            else if(enemyPokeID == 4){enemyPoke = Torc2;}
                            else if(enemyPokeID == 6){enemyPoke = Osha2;}

                            allyPokeID = (tiles[file][rank]->getPokemon().getID());
                            if(allyPokeID==1){allyPoke=Bulb1;}
                            if(allyPokeID==2){allyPoke=Turt1;}
                            if(allyPokeID==3){allyPoke=Char1;}
                            if(allyPokeID==4){allyPoke=Torc1;}
                            if(allyPokeID==5){allyPoke=Squi1;}
                            if(allyPokeID==6){allyPoke=Osha1;}

                            return true;
                        }   
                        //If it is player 1's turn, and the pokemon to the right belongs to player 1, return false.
                        else if(((tiles[file-row][rank])->getPokemon().playerNo) == 1 && player1turn == true){
                            return false;
                        }
                        //If it is player 2's turn, and the pokemon to the left belongs to player 2, return false.
                        else if(((tiles[file+row][rank])->getPokemon().playerNo) == 2 && player1turn == false){
                            return false;
                        }
                        //If it is player 1's turn, and the pokemon to the right belongs to player 2, return true.
                        else if(((tiles[file-row][rank])->getPokemon().playerNo) == 2 && player1turn == true){
                            return true;
                        }
                        else{
                            std::cout<<"No Adjacent Pokemon"<<std::endl;
                            return false;
                        }
                    
                } return false;
            }else{
                return false;
            }

                    
    }

void Map::createCursor(){ //creating a cursor
    this -> cursorImage.loadFromFile("files/cursor.png");
    this -> cursorSprite.setTexture(cursorImage);
    this -> cursorX = 0;
    this -> cursorY = 0;
}

// get the cursor sprite
sf::Sprite Map::getCursor(){
    this -> cursorSprite.setPosition(cursorX, cursorY);
    return this -> cursorSprite;
}

//for cursor movement
void Map::cursorUp(){
    this -> cursorY = cursorY - tileSize; 
        if(this -> cursorY < 0){
            std::cout <<"Cannot go out of bounds" << std::endl;

            this -> cursorY = cursorY + tileSize;  
            
        }
}

void Map::cursorDown(){
    this -> cursorY = cursorY + tileSize;
        if(this -> cursorY > tileSize * 7){
            std::cout <<"Cannot go out of bounds" << std::endl;
            this -> cursorY = cursorY - tileSize ;
        }
}

void Map::cursorLeft(){
    this -> cursorX = cursorX - tileSize;
        if(this -> cursorX < 0){
            std::cout <<"Cannot go out of bounds" << std::endl;
            this -> cursorX = cursorX + tileSize;
        }
}

void Map::cursorRight(){
    this -> cursorX = cursorX + tileSize;
        if(this -> cursorX > tileSize * 7){
            std::cout << "Cannot go out of bounds" << std::endl;
            this -> cursorX = cursorX - tileSize;
        }
} 

// get the tile that we are on
Tile Map::getTile(int x, int y){
    return *this -> tiles[x][y];
}

// clearing heap memory after used
Map::~Map(){
    for (int r = 0; r < 8; r++){
        for (int c = 0; c < 8; c++){
            delete this -> tiles[r][c];
        }
    }
}
//Get what pokemon by finding the ID
PokemonBase Map::getPBase(int ID){
    // So with the given ID, a pokemon will be returned, we store this in a temp in Game.cpp and it works for creating a new pokemon on a new tile, so progress, but it only 
    // creates a new pokemon of the else{}, the other if() seem to not work even tho i have checked the ID is a int from 1-6 or whatever.
    if (ID == 1){
        return Bulb1;
    }
    else if(ID == 2){
        return Char1;
    } 
    else if(ID == 3){
        return Squi1;
    }
    else if(ID == 4){
        return Turt1;
    } 
    else if(ID == 5){
        return Torc1;
    }
    else if(ID == 6){
        return Osha1;
    } 
    else{
        return Bulb1;
    }

}