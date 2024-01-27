#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
//class for each player, determines sides and playerTurns
class Player{
    bool leftSide; //determines which side the player starts
    int pokemonLeft; //How many pokemon are left
    public:
    Player();
    Player(bool leftOrRight); //What player we are on
    void losePokemon(); //remove a pokemonLeft if one on their side loses all HP
    int returnPokemonLeft(); //return a pokemon
    bool getAlignment(); //which side are we on
    ~Player();
};
#endif //PLAYER_H