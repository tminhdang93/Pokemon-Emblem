#include "Attack.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "PokemonBase.h"
#include <iostream>
int main(){
    Bulbasaur Bulbasaur(true);
    for (int i = 0; i < 4; i++){
        Bulbasaur.getMove(i).returnAttackDesc(); //testing if moves are set up right and can be shown
    }
    //checking is moves are created right
    StatusAttack attack("Status Attack", 1, 0, true, "1", "Temp status attack");
    attack.returnAttackDesc();
    TypeAttack attack2("Fire attack", 40, 2, 2, false, "Temp fire attack");
    attack2.returnAttackDesc(); 
    NormalAttack attack3("Normal attack", 40, 0, true,"Temp normal attack");
    attack3.returnAttackDesc(); 
}