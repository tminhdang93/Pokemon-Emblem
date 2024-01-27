#ifndef POKEMONBASE_H
#define POKEMONBASE_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Attack.h"

class PokemonBase{ //the base Pokemon (does not change once defined) - also contains current stats
    protected:

    int pID; //pokemon's number ID. Used to define sprites
    int pTypeInt; //pokemon's type. int is used for if statements regarding type matchups grass = 1, fire = 2, water = 3
    std::string pTypeString; //type in string (for log)
    //base stats at level 1
    int bAtk; //base attack
    int bDef; //base defense
    int bHP; //base max HP
    int mov; //movement - 3 for each pokemon (used to check the maximum amount of spaces they can move)
    int bLevel; //base level (1)
    //texture/sprites for each Pokemon
    sf::Texture pTexture;
    sf::Sprite pSprite;
    int tileSize; //Size of tile 
    //create current stats for the pokemon (can be updated)
    int cMaxHP;
    int cLevel;
    int exp; //gain exp after each battle phase, 100 EXP is needed to level up
    std::string infoString; //information about pokemon
    bool pAlignment; //Make sure pokemon is alinged correctly
    int baseDamage; //calculate damage for attacks

    public:
    std::string pName; //pokemon's name
    Attack *moveset[4]; //Each pokemon holds a moveset containing an array of four attack objects.
    //Current stats
    int cHP; //current HP (after taking damage)
    int cDef; //moved here
    int cAtk;
    int playerNo; //keep track if different pokemon is used
    //Creating pokemon
    PokemonBase();
    PokemonBase(int id, std::string name, int typeInt, int atk, int def, int hp); 
    std::string getType(); //get the string of type from int
    int getID(); //return pokemon ID
    sf::Sprite getSprite(int x, int y); //get sprite for the pokemon

    //update stats, levels etc.
    void updateAtk(int value); 
    void updateDef(int value); 
    void updateMaxHP(int value);
    void updateCHP(int damageTaken);

    //get attack, defense, level, and current health for attack calculation
    int getAtk();
    int getDef();
    int getLevel();
    int getCHP();

    //leveling up and gainig exp
    void levelUp();
    void gainEXP(int value); 
    void printStats(); //printing stats - for testing

    //get moves and calculate damage 
    Attack getMove(int i);
    void printMoveset(); 

    //Variables to handle status moves.
    bool statusPoison;
    bool statusBurn;
    bool statusLeech;
    bool statusWhirl;
    bool statusBleed;
    bool statusParalysis;
    //Functions to set and clean status conditions.
    void modifyStatus(std::string);
    void cleanStatusConditions(); //Resets all status conditions to false.
    //Functions to apply the effects of status conditions.
    void applyStatusPoison();
    void applyStatusBurn();
    float applyStatusLeech(); //Returns the damage dealt, so it can heal the applying pokemon.
    void applyStatusWhirl();
    void applyStatusBleed();
    bool applyStatusParalysis(); //Returns true/false, to decide whether or not to skip turn.

    ~PokemonBase();
};

//create individual classes for each Pokemon as each instance of one will have set base stats and properties
class Bulbasaur: public PokemonBase{
    public:
    Bulbasaur(bool alignment);
    void initialiseMoves();
    ~Bulbasaur();
};

class Turtwig: public PokemonBase{
    public:
    Turtwig(bool alignment);
    void initialiseMoves();
    ~Turtwig();
};

class Charmander: public PokemonBase{
    public:
    Charmander(bool alignment);
    void initialiseMoves();
    ~Charmander();
};

class Torchic: public PokemonBase{
    public:
    Torchic(bool alignment);
    void initialiseMoves();
    ~Torchic();
};

class Squirtle: public PokemonBase{
    public:
    Squirtle(bool alignment);
    void initialiseMoves();
    ~Squirtle();
};

class Oshawott: public PokemonBase{
    public:
    Oshawott(bool alignment);
    void initialiseMoves();
    ~Oshawott();
};

#endif //PokemonBase

