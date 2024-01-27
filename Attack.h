#ifndef ATTACK_H
#define ATTACK_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
class Attack{
    protected:
    std::string aDescription; //a brief description of the attack
    int aPower; //power of the attack - used in damage calcualtion
    int aTypeInt; //attack type. int is used for if statements regarding type matchups grass = 1, fire = 2, water = 3
    std::string aTypeString; //type in string (for log)
    int aLevel; //set unlock level of the attack
    bool unlocked; //determines if the attack can be used at the Pokemon's current level.
    public:
    int buffNo; //Corresponds to what type of buff a move is;
    std::string aName; //attack name
    Attack();
    Attack(std::string name, int power, int type, int level, bool unlock, std::string description);
    std::string getType(); //get the string of type from int
    float getPower(); //return power
    void returnAttackDesc(); //return attack description
    std::string statusApplied; //Handles status effects; 0 = none, 1 = poison, 2 = burn, 3 = leech, 4 = whirl, 5 = bleed, 6 = sleep.
    std::string getStatusApplied(); //Retrieves statusApplied.
    ~Attack();
    };

class StatusAttack: public Attack{ //non-damaging attacks - power of 0 - does not call damage
protected:
public:
StatusAttack(std::string name, int type, int level, bool unlock, std::string statusApp,std::string description);
~StatusAttack();
};

class DamageAttack: public Attack{ //damaging attacks - will call a damage function
protected:
public:
DamageAttack(std::string name, int power, int type, int level, bool unlock, std::string description);
DamageAttack();
~DamageAttack();
};

class TypeAttack: public DamageAttack{ //attacks with a type - will have a modifier for matchups
protected:
public:
TypeAttack(std::string name, int power, int type, int level, bool unlock, std::string description);
~TypeAttack();
};

class NormalAttack: public DamageAttack{ //normal-type attacks - no damage modifiers
protected:
public:
NormalAttack(std::string name, int power, int level, bool unlock, std::string description);
~NormalAttack();
};

#endif //ATTACK_H