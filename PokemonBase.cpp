#include "PokemonBase.h"
#include <iostream>
#include "string.h"
#include "Tile.h"
#include "Map.h"
#include "Game.h"
#include <time.h>
#include <cstdlib>

// For Creating a pokemon
PokemonBase::PokemonBase(int id, std::string name, int typeInt, int atk, int def, int hp){
    //Setting stats
    this -> pID = id;
    this -> pName = name;
    this -> pTypeInt = typeInt;
    this -> bAtk = atk;
    this -> bDef = def;
    this -> bHP = hp;
    this -> mov = 3;
    this -> cAtk = atk;
    this -> cDef = def;
    this -> cMaxHP = hp;
    this -> cHP = hp;
    this -> bLevel = 1;
    this -> cLevel = 1;
    this -> exp = 0;
    this -> infoString = "Pokemon: " + this -> pName + " | " + "Type " + this -> getType() + " | " + "Level: " + std::to_string(this -> cLevel) + 
                 " | " + "Current Health: " + std::to_string(this -> cHP) + "/" + std::to_string(this -> cMaxHP) + " | " + "Attack: " 
                 + std::to_string(this -> cAtk) + " | " + "Defense: " + std::to_string(this -> cDef) + " | " + "Movement: " + std::to_string(this -> mov);
    this -> tileSize = 150;
    //Variables to handle status moves.
    this -> statusPoison = false;
    this -> statusBurn = false;
    this -> statusLeech = false;
    this -> statusWhirl = false;
    this -> statusBleed = false;
    this -> statusParalysis = false;
};

// Empty Pokemons
PokemonBase::PokemonBase(){
    //Setting stats
    this ->playerNo = 0;
    this -> pID = 0;
    this -> pName = "Null";
    this -> pTypeInt = 0;
    this -> bAtk = 0;
    this -> bDef = 0;
    this -> bHP = 0;
    this -> mov = 0;
    this -> cAtk = 0;
    this -> cDef = 0;
    this -> cMaxHP = 0;
    this -> cHP = 0;
    this -> bLevel = 0;
    this -> cLevel = 0;
    this -> exp = 0;
    this -> infoString = "Pokemon: " + this -> pName + " | " + "Type " + this -> getType() + " | " + "Level: " + std::to_string(this -> cLevel) + 
                 " | " + "Current Health: " + std::to_string(this -> cHP) + "/" + std::to_string(this -> cMaxHP) + " | " + "Attack: " 
                 + std::to_string(this -> cAtk) + " | " + "Defense: " + std::to_string(this -> cDef) + " | " + "Movement: " + std::to_string(this -> mov);
    this -> tileSize = 0;
    //Variables to handle status moves.
    this -> statusPoison = false;
    this -> statusBurn = false;
    this -> statusLeech = false;
    this -> statusWhirl = false;
    this -> statusBleed = false;
    this -> statusParalysis = false;
}

// Get type
std::string PokemonBase::getType(){
    switch (this -> pTypeInt){ //checking what type string is set
    case 1:
        this -> pTypeString = "Grass";
        break;
    case 2:
        this -> pTypeString = "Fire";
        break;
    case 3:
        this -> pTypeString = "Water";
        break;
    default:
       this -> pTypeString = "Null";
    }
    return this -> pTypeString;
}

//Get ID
int PokemonBase::getID(){
    return pID;
}

//Update current stats
void PokemonBase::updateAtk(int value){
    this -> cAtk = this -> cAtk + value;
    if (value < 0){
        std::cout << this -> pName << " lost " << value << " Attack" << std::endl;
    }else{
        std::cout << this -> pName << " gained " << value << " Attack" << std::endl;
    }
}
void PokemonBase::updateDef(int value){
    this -> cDef = this -> cDef + value;
    if (value < 0){
        std::cout << this -> pName << " lost " << value << " Defense" << std::endl;
    }else{
        std::cout << this -> pName << " gained " << value << " Defense" << std::endl;
    }
}
void PokemonBase::updateMaxHP(int value){
    this -> cMaxHP = this -> cMaxHP + value;
    this -> cHP = this -> cHP + value;
    if (value < 0){
        std::cout << this -> pName << " lost " << value << " HP" << std::endl;
    }else{
        std::cout << this -> pName << " gained " << value << " HP" << std::endl;
    }
}
void PokemonBase::updateCHP(int damageTaken){
    this -> cHP = this -> cHP - damageTaken;
    std::cout<<this -> pName << " took "<<damageTaken<<" damage"<<std::endl;
}

// Return current stats
int PokemonBase::getAtk(){return this -> cAtk;}
int PokemonBase::getDef(){return this -> cDef;}
int PokemonBase::getLevel(){return this -> cLevel;}
int PokemonBase::getCHP(){return this -> cHP;}

// For levelling
// Did not use
void PokemonBase::levelUp(){
    srand(time(NULL));
    this -> cLevel = this -> cLevel + 1;
    std::cout << this -> pName << " reached level " << this -> cLevel << std::endl;
    this -> updateAtk(1 + rand() % 3);
    this -> updateDef(1 + rand() % 3);
    this -> updateMaxHP(1 + rand() % 3);
}
void PokemonBase::gainEXP(int value){
    this -> exp = this -> exp + value;
    std::cout << this -> pName << " gained " << value << " EXP" << std::endl;
    if(this -> exp >= 100){
        this -> levelUp();
        this -> exp = 0;
    }
}
//Inputs a status as a string; if the status is valid, the condition is applied to the pokemon.
//I don't know if I'm using 'this ->' correctly.
void PokemonBase::modifyStatus(std::string appliedStatus){
    if(appliedStatus == "poison"){this -> statusPoison = true;}
    if(appliedStatus == "burn"){this -> statusBurn = true;}
    if(appliedStatus == "leech"){this -> statusLeech = true;}
    if(appliedStatus == "whirl"){this -> statusWhirl = true;}
    if(appliedStatus == "bleed"){this -> statusBleed = true;}
    if(appliedStatus == "paralysis"){this -> statusParalysis = true;}
}

//Cleans the pokemon of their status conditions; useful after a battle ends.
void PokemonBase::cleanStatusConditions(){
    this -> statusPoison = false;
    this -> statusBurn = false;
    this -> statusLeech = false;
    this -> statusWhirl = false;
    this -> statusBleed = false;
    this -> statusParalysis = false;
}

//The functions below modify the pokemon based on its current status.
void PokemonBase::applyStatusPoison(){
    //Poison deals 25% of the target's max hp per turn.
    if(this -> statusPoison == true){
        this -> cHP -= (bHP/4);
        std::cout<<pName<<" took "<<bHP/4<<" damage from poison!"<<std::endl;
    }
}
void PokemonBase::applyStatusBurn(){
    //Burn deals a sixth of the target's max hp per turn.
    if(this -> statusBurn == true){
        this -> cHP -= (bHP/6);
        std::cout<<pName<<" took "<<bHP/6<<" damage from burn!"<<std::endl;
    }
}
float PokemonBase::applyStatusLeech(){
    //Leech deals an eighth of the target's max hp per turn and heals for the damage dealt.
    if(this -> statusLeech == true){
        this -> cHP -= (bHP/8);
        std::cout<<pName<<" took "<<bHP/8<<" damage from leech seed!"<<std::endl;
        return -(bHP/8);
    }
    return 0;
}
void PokemonBase::applyStatusWhirl(){
    //Whirl deals a sixth of the target's max hp per turn.
    if(this -> statusWhirl == true){
        this -> cHP -= (bHP/6);
        std::cout<<pName<<" took "<<bHP/6<<" damage from the whirlpool!"<<std::endl;
    }
}
void PokemonBase::applyStatusBleed(){
    //Bleed deals a fifth of the target's max hp per turn.
    if(this -> statusBleed == true){
        this -> cHP -= (bHP/5);
        std::cout<<pName<<" took "<<bHP/5<<" damage from the bleed!"<<std::endl;
    }
}
bool PokemonBase::applyStatusParalysis(){
    //Paralysis has a 40% chance to occur and disables the target's move.
    srand(time(NULL)); //Randomizes the seed based on system time.
    int randomParalysis = rand() % 10 + 1; //Generates a random number between 1 and 10 and assigns it to 'randomParalysis'.
    if(this -> statusParalysis == true){
        if(randomParalysis < 5){ //If random number is from 1 to 4 (40% chance), the pokemon is paralyzed.
            std::cout<<pName<<" was paralyzed. They are unable to move."<<std::endl;
            return true;
        }
    }
    return false;
}

sf::Sprite PokemonBase::getSprite(int x, int y){
    //Checks if the texture file is avalaible.
    if (!pTexture.loadFromFile("files/pokemonSprites.png")){
        std::cout << "cannot find texture for sprite" << std::endl;
        return pSprite;
    }
    //Checks if the pokemon's ID has a corresponding texture.
    if(this -> pID <= 0 && this -> pID >= 7){
        std::cout << "cannot set sprite" <<std::endl;
        return pSprite;
    }
    this -> pSprite.setTexture(pTexture); //Sets the texture file to the sprite.
    //Sets the texture to the specific section of the texture file that corresponds to the pokemon.
    this -> pSprite.setTextureRect(sf::IntRect(tileSize * (this -> pID - 1), 0, tileSize, tileSize)); 
    //Sets the position of the texture relative to top left, scaled by tileSize.
    this -> pSprite.setPosition(tileSize * x, tileSize * y);
    return this -> pSprite;
}

//Print stats
void PokemonBase::printStats(){
    std::cout << "\n";
    this -> infoString = "Pokemon: " + this -> pName + " | " + "Type " + this -> getType() + " | " + "Level: " + std::to_string(this -> cLevel) + 
                 " | " + "Current Health: " + std::to_string(this -> cHP) + "/" + std::to_string(this -> cMaxHP) + " | " + "Attack: " 
                 + std::to_string(this -> cAtk) + " | " + "Defense: " + std::to_string(this -> cDef) + " | " + "Movement: " + std::to_string(this -> mov);
    std::cout << this -> infoString << std::endl;
}

//return what move they chose
Attack PokemonBase::getMove(int i){return *this -> moveset[i];}

// print moveset
void PokemonBase::printMoveset(){
    std::cout << "\n";
    for(int i=0;i<4; i++){
        this -> moveset[i]-> returnAttackDesc();
    }
    std::cout << "\n";
}

//Deconstructor
PokemonBase::~PokemonBase(){}

//Creating specific pokemon
Bulbasaur::Bulbasaur(bool alignment){ //1, "Bulbasaur", 1, 49, 49, 45
    this -> pID = 1;
    this -> pName = "Bulbasaur";
    this -> pTypeInt = 1;
    this -> bAtk = 49;
    this -> bDef = 49;
    this -> bHP = 45;
    this -> mov = 3;
    this -> cAtk = bAtk;
    this -> cDef = bDef;
    this -> cMaxHP = bHP;
    this -> cHP = bHP;
    this -> bLevel = 1;
    this -> cLevel = 1;
    this -> exp = 0;
    this -> pAlignment = alignment;
    this -> tileSize = 150;
    this -> initialiseMoves();
}
//Type Attack: Name, Power, Type (Int), Level (Unused), unlockStatus (Unused), Description.
//Status Attack: Name, Type (Int), Level (Unsued), unlockStatus (Unused), Status Applied, Description.
void Bulbasaur::initialiseMoves(){
    this -> moveset[0] = new TypeAttack("Vine Whip", 55, 0, 0, true, "Grass Type: Strikes the target with a pair of vine whips.");
    this -> moveset[1] = new TypeAttack("Seed Bomb", 60, 1, 5,false, "Grass Type: Barrages seeds at the target.");
    this -> moveset[2] = new StatusAttack("Growl", 4, 0, true,"null", "Reduces the target's attack.");
    this -> moveset[3] = new StatusAttack("Poison Powder", 1, 0, true, "poison", "Poisons the target.");
}
Bulbasaur::~Bulbasaur(){}

Turtwig::Turtwig(bool alignment){
    this -> pID = 2;
    this -> pName = "Turtwig";
    this -> pTypeInt = 1;
    this -> bAtk = 68;
    this -> bDef = 64;
    this -> bHP = 55;
    this -> mov = 3;
    this -> cAtk = bAtk;
    this -> cDef = bDef;
    this -> cMaxHP = bHP;
    this -> cHP = bHP;
    this -> bLevel = 1;
    this -> cLevel = 1;
    this -> exp = 0;
    this -> pAlignment = alignment;
    this -> tileSize = 150;
    this -> initialiseMoves();
}
//Type Attack: Name, Power, Type (Int), Level (Unused), unlockStatus (Unused), Description.
//Status Attack: Name, Type (Int), Level (Unsued), unlockStatus (Unused), Status Applied, Description.
void Turtwig::initialiseMoves(){
    this -> moveset[0] = new NormalAttack("Tackle", 40, 0, true, "Normal Type: Rams the target.");
    this -> moveset[1] = new TypeAttack("Razor Leaf", 45, 1, 4, false, "Grass Type: Unleashes a barrage of leaves at the target.");
    this -> moveset[2] = new StatusAttack("Withdraw", 3, 0, true,"null", "Raises own defense.");
    this -> moveset[3] = new StatusAttack("Leech Seed", 1, 0, true, "leech", "Leeches the target, damaging them over time.");
    
}
Turtwig::~Turtwig(){}

Charmander::Charmander(bool alignment){
    this -> pID = 3;
    this -> pName = "Charmander";
    this -> pTypeInt = 2;
    this -> bAtk = 52;
    this -> bDef = 43;
    this -> bHP = 49;
    this -> mov = 3;
    this -> cAtk = bAtk;
    this -> cDef = bDef;
    this -> cMaxHP = bHP;
    this -> cHP = bHP;
    this -> bLevel = 1;
    this -> cLevel = 1;
    this -> exp = 0;
    this -> pAlignment = alignment;
    this -> tileSize = 150;
    this -> initialiseMoves();
}
//Type Attack: Name, Power, Type (Int), Level (Unused), unlockStatus (Unused), Description.
//Status Attack: Name, Type (Int), Level (Unsued), unlockStatus (Unused), Status Applied, Description.
void Charmander::initialiseMoves(){
    this -> moveset[0] = new NormalAttack("Scratch", 40, 0, true, "Normal Type: Scratches the target.");
    this -> moveset[1] = new TypeAttack("Ember", 40, 2, 0, true, "Fire Type: Releases a stream of embers at the target.");
    this -> moveset[2] = new StatusAttack("Scary Face", 4, 3, false,"null", "Reduces the target's attack");
    this -> moveset[3] = new StatusAttack("Inferno", 2, 0, true, "burn", "Burns the target.");
}
Charmander::~Charmander(){}

Torchic::Torchic(bool alignment){
    this -> pID = 4;
    this -> pName = "Torchic";
    this -> pTypeInt = 2;
    this -> bAtk = 60;
    this -> bDef = 40;
    this -> bHP = 45;
    this -> mov = 3;
    this -> cAtk = bAtk;
    this -> cDef = bDef;
    this -> cMaxHP = bHP;
    this -> cHP = bHP;
    this -> bLevel = 1;
    this -> cLevel = 1;
    this -> exp = 0;
    this -> pAlignment = alignment;
    this -> tileSize = 150;
    this -> initialiseMoves();

}
//Type Attack: Name, Power, Type (Int), Level (Unused), unlockStatus (Unused), Description.
//Status Attack: Name, Type (Int), Level (Unsued), unlockStatus (Unused), Status Applied, Description.
void Torchic::initialiseMoves(){
    this -> moveset[0] = new TypeAttack("Ember", 50, 0, 0, true, "Fire Type: Releases a stream of embers at the target.");
    this -> moveset[1] = new TypeAttack("Fire Fang", 50, 2, 4, false, "Fire Type: Crunches the target with flaming fangs.");
    this -> moveset[2] = new StatusAttack("Focus Energy", 4, 2, false,"null", "Raises attack strongly");
    this -> moveset[3] = new StatusAttack("Slash", 0, 0, true, "bleed", "Bleeds the target.");
}
Torchic::~Torchic(){}

Squirtle::Squirtle(bool alignment){
    this -> pID = 5;
    this -> pName = "Squirtle";
    this -> pTypeInt = 2;
    this -> bAtk = 48;
    this -> bDef = 65;
    this -> bHP = 44;
    this -> mov = 3;
    this -> cAtk = bAtk;
    this -> cDef = bDef;
    this -> cMaxHP = bHP;
    this -> cHP = bHP;
    this -> bLevel = 1;
    this -> cLevel = 1;
    this -> exp = 0;
    this -> pAlignment = alignment;
    this -> tileSize = 150;
    this -> initialiseMoves();
}
//Type Attack: Name, Power, Type (Int), Level (Unused), unlockStatus (Unused), Description.
//Status Attack: Name, Type (Int), Level (Unsued), unlockStatus (Unused), Status Applied, Description.
void Squirtle::initialiseMoves(){
    this -> moveset[0] = new NormalAttack("Tackle", 40, 0, true, "Normal Type: Rams the target.");
    this -> moveset[1] = new TypeAttack("Aqua Tail", 60, 3, 5, false, "Water Type: Strikes the target with a watery tail.");
    this -> moveset[2] = new StatusAttack("Tail Whip", 4, 0, true,"null", "Reduces target's defense");
    this -> moveset[3] = new StatusAttack("Whirlpool", 3, 0, true, "whirl", "Traps the target in a damaging whirlpool.");
}
Squirtle::~Squirtle(){}

Oshawott::Oshawott(bool alignment){
    this -> pID = 6;
    this -> pName = "Oshawott";
    this -> pTypeInt = 3;
    this -> bAtk = 55;
    this -> bDef = 45;
    this -> bHP = 35;
    this -> mov = 3;
    this -> cAtk = bAtk;
    this -> cDef = bDef;
    this -> cMaxHP = bHP;
    this -> cHP = bHP;
    this -> bLevel = 1;
    this -> cLevel = 1;
    this -> exp = 0;
    this -> pAlignment = alignment;
    this -> tileSize = 150;
    this -> initialiseMoves();
}
//Type Attack: Name, Power, Type (Int), Level (Unused), unlockStatus (Unused), Description.
//Status Attack: Name, Type (Int), Level (Unsued), unlockStatus (Unused), Status Applied, Description.
void Oshawott::initialiseMoves(){
    this -> moveset[0] = new TypeAttack("Water Gun", 50, 0, 0, true, "Water Type: Spews a powerful burst of water at the target.");
    this -> moveset[1] = new NormalAttack("Tackle", 40, 3, true, "Normal Type: Rams the target.");
    this -> moveset[2] = new StatusAttack("Swords Dance", 4, 5, false,"null", "Raises attack strongly");
    this -> moveset[3] = new StatusAttack("Paralysis Shell", 0, 0, true, "paralysis", "Paralyses the target.");
}
Oshawott::~Oshawott(){}