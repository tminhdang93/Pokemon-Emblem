#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Map.h"
#include "Menu.h"

/**
 * Game.h file which contains the game's engine as well as all other classes.
 * Used to start the game on main.
 */
class Game{
    private:
        //Variables which handle the game window, events, and font used.
        sf::RenderWindow *gameWindow; 
        sf::Event ev; 
        sf::Font font; 
        //Functions to set up the game window.
        void initialiseVariables(); //initialise game window as a pointer
        void initialiseWindow(int width, int height); //initialise window with window height and width
        MainMenu mainMenu; //= MainMenu(700, 1100, 4); the main menu when initialising the game
        //Variables to handle menu switching, pokemon selection, and movement.
        int currentMenu; //Sets the current section of the game in play.
        bool pokemonSelected;
        int movesLeft;
        //Variables used to handle move choice and turns during battle phase.
        int playerMoveChoice;
        int currentTurn;
        //Creates text variables that are then displayed on the game window.
        sf::Text howToPlay;
        sf::Text buttonControls;

    public:
        Attack move; //stores what move the player inputs 
        //counters for who wins
        int winCountp1;
        int winCountp2;
        // variable, used for calculating damage of an attack
        float attackDamage;
        // temp coords
        int tempX;
        int tempY;
        // another temp pokemon
        PokemonBase wastepokemon;
        // Which turn are we won
        bool p1Turn; 
        bool tempp1Turn;
        // Spare pokemon
        PokemonBase tempPokemon;
        // count to see if a square is clicked on or not
        int count;
        Map sBoard; //sprite of the map; object under 'Map' class.
        Game();
        bool running(); //check if window is open
        void loadMap(); //load the sprite of the board onto the screen
        void defineTextObjects(); //load non-menu/log text objects
        PokemonBase findNearPokemon(Tile currentTile);
        float calcDmg(PokemonBase AtkPoke, PokemonBase DefPoke, Attack Attack); //Returns damage value given two pokemon and an attack.
        //void calcBoostAttack(PokemonBase AtkPoke, PokemonBase DefPoke, StatusAttack Attack);
        void incAtkAlly(PokemonBase AtkPoke);
        void incDefAlly(PokemonBase AtkPoke);
        void decAtkEnemy(PokemonBase DefPoke);
        void decDefEnemy(PokemonBase DefPoke);


        //Event functions.
        void closeEvent(); //Closes game window upon receiving a request to close to game window.
        void buttonEvent();//determines actions in the main menu
        void eventControl(); //check for events

        //main functions while the game is running
        void update(); //perform actions
        void render(); //visualise positions on screen
        ~Game();
};
#endif //GAME_H