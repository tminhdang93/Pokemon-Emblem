#include "Attack.h"
#include <iostream>

Attack::Attack(){ // default constructor
    this -> aName = "NULL";
    this -> aPower = 0;
    this -> aTypeInt = 0;
    this -> unlocked = false;
    this -> aLevel = 0;
    this -> aDescription = "NULL ATTACK";
    this -> statusApplied = "NULL";
}

Attack::Attack(std::string name, int power, int type, int level, bool unlock, std::string description){
    this -> aName = name;
    this -> aPower = power;
    this -> aTypeInt = type; 
    this -> aLevel = level;
    this -> unlocked = unlock;
    this -> statusApplied = "NULL";
    this -> aDescription = description;
}

std::string Attack::getType(){ //return attack type
    switch (this -> aTypeInt){
    case 1:
        this -> aTypeString = "Grass";
        break;
    case 2:
        this -> aTypeString = "Fire";
        break;
    case 3:
        this -> aTypeString = "Water";
        break;
    case 4:
        this -> aTypeString = "Normal";
        break;
    default:
        this -> aTypeString = "Null";
    }
    return this -> aTypeString;
}

float Attack::getPower(){ return this -> aPower;} //return attack
std::string Attack::getStatusApplied(){return this -> statusApplied;} //return status applied

void Attack::returnAttackDesc(){ // print attack descriptions
    std::cout << this -> aName << " | Power: " << this -> aPower << " | " << this -> getType() << " | " << this -> aDescription << std::endl;
}
Attack::~Attack(){} //Deconstructor

StatusAttack::StatusAttack(std::string name, int type, int level, bool unlock, std::string statusApp,std::string description){
    this -> aName = name;
    this -> aPower = 0;
    this -> aTypeInt = type;
    this -> aLevel = level;
    this -> unlocked = unlock;
    this -> statusApplied = statusApp;
    this -> aDescription = description;
}
StatusAttack::~StatusAttack(){} //Deconstructor
//Below are attacks
DamageAttack::DamageAttack(std::string name, int power, int type, int level, bool unlock, std::string description){
    this -> aName = name;
    this -> aPower = power;
    this -> aTypeInt = type;
    this -> aLevel = level;
    this -> unlocked = unlock;
    this -> aDescription = description;
}

DamageAttack::DamageAttack(){
    this -> aName = "NULL";
    this -> aPower = 0;
    this -> aTypeInt = 0;
    this -> aLevel = 0;
    this -> unlocked = false;
    this -> aDescription = "NULL ATTACK";
}

DamageAttack::~DamageAttack(){}

TypeAttack::TypeAttack(std::string name, int power, int type, int level, bool unlock, std::string description)
:DamageAttack(){
    this -> aName = name;
    this -> aPower = power;
    this -> aTypeInt = type;
    this -> aLevel = level;
    this -> unlocked = unlock;
    this -> aDescription = description;
}

TypeAttack::~TypeAttack(){}

NormalAttack::NormalAttack(std::string name, int power, int level, bool unlock, std::string description)
:DamageAttack(){
    this -> aName = name;
    this -> aPower = power;
    this -> aTypeInt = 4;
    this -> aLevel = level;
    this -> unlocked = unlock;
    this -> aDescription = description;
}

NormalAttack::~NormalAttack(){}