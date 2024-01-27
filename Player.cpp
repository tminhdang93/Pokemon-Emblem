#include <iostream>
#include "Player.h"
// Creating a player
Player::Player(){
    this -> leftSide = true;
    this -> pokemonLeft = 6;
}

Player::Player(bool leftOrRight){
    this -> leftSide = leftOrRight;
    this -> pokemonLeft = 6;
}

//Losing a pokemon
void Player::losePokemon(){
    if(this -> pokemonLeft <=0){
        std::cout << "No more Pokemon" << std::endl;
    }
    else{
        this -> pokemonLeft = pokemonLeft - 1;
    }
}

// return pokemon that are remaning
int Player::returnPokemonLeft(){
    return this -> pokemonLeft;
}

//return which side was started on
bool Player::getAlignment(){
    return this -> leftSide;
}

Player::~Player(){

}