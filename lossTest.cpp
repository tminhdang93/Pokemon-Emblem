#include <iostream>
#include "Player.h"

//Testing what happens when a pokemon is lost.
int main(){
    Player p1(true);
    std::cout << "Player 1 has " << p1.returnPokemonLeft() << " Pokemon left." << std::endl;
    p1.losePokemon();
    std::cout << "Player 1 has " << p1.returnPokemonLeft() << " Pokemon left." << std::endl;
    p1.losePokemon();
    std::cout << "Player 1 has " << p1.returnPokemonLeft() << " Pokemon left." << std::endl;
    p1.losePokemon();
    std::cout << "Player 1 has " << p1.returnPokemonLeft() << " Pokemon left." << std::endl;
    p1.losePokemon();
    std::cout << "Player 1 has " << p1.returnPokemonLeft() << " Pokemon left." << std::endl;
    p1.losePokemon();
    std::cout << "Player 1 has " << p1.returnPokemonLeft() << " Pokemon left." << std::endl;
    p1.losePokemon();
    std::cout << "Player 1 has " << p1.returnPokemonLeft() << " Pokemon left." << std::endl;
    p1.losePokemon();
    std::cout << "Player 1 has " << p1.returnPokemonLeft() << " Pokemon left." << std::endl;
    p1.losePokemon();
    std::cout << "Player 1 has " << p1.returnPokemonLeft() << " Pokemon left." << std::endl;
    p1.losePokemon();
    std::cout << "Player 1 has " << p1.returnPokemonLeft() << " Pokemon left." << std::endl;
}