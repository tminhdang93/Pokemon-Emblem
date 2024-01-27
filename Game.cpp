#include <iostream>
#include "Game.h"

void Game::initialiseVariables(){
    mainMenu = MainMenu(700, 1100, 4);
    this -> gameWindow = nullptr;
    //Creating the menu 
}

void Game::initialiseWindow(int width, int height){ //set title
    this -> gameWindow = new sf::RenderWindow(sf::VideoMode(width, height), "Pokemon Emblem", sf::Style::Titlebar | sf::Style::Close);
}

Game::Game(){ //initialise important variables
    this ->initialiseVariables();
    this ->initialiseWindow(1900, 1200);
    mainMenu.establishMenu();
    defineTextObjects();
    currentMenu = 0;
    pokemonSelected = false;
    p1Turn = true;
    playerMoveChoice = 0;
    currentTurn = 0;
    count = 0;
    winCountp1 = 0;
    winCountp2 = 0;
}

bool Game::running(){
    return this->gameWindow->isOpen(); 
}

void Game::loadMap(){ //drawing the board and tiles
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            this -> gameWindow -> draw(sBoard.getTile(i, j).getTileSprite());
                if(sBoard.getTile(i, j).getPokemon().getID() > 0 && sBoard.getTile(i, j).getPokemon().getID() < 7){
                    this -> gameWindow -> draw(sBoard.getTile(i, j).getPokemon().getSprite(i, j));
                }
            }
        }
}

void Game::defineTextObjects(){ //for text objects in UI
    if(!font.loadFromFile("files/ChicagoFLF.ttf")){std::cout << "cannot find font" <<std::endl;}
    //Text display which explains how to play the game.
    howToPlay.setFont(font);
    howToPlay.setFillColor(sf::Color::White);
    howToPlay.setString("Pokemon Emblem is a turn based game.\n\nTurns alternate between two players \n"
                        "where one player moves a Pokemon\nbefore the next player.\n\nPlayers can enter "
                        "a battle when next\nto an opposing Pokemon, where both\nplayers pick a move to use.\n"
                        "\nThe game ends when one player loses all\nof their Pokemon.");
    howToPlay.setPosition(sf::Vector2f(1200, 1200/(4 + 1) * 1));
    //Text display which explains game keybinds.
    buttonControls.setFont(font);
    buttonControls.setFillColor(sf::Color::White);
    buttonControls.setString("Arrow Keys: Movement\nZ Key: Confirm(Press 2x to select Poke) \nX Key: Cancel\nC Key (during battle): Settings");
    buttonControls.setPosition(sf::Vector2f(1200, 1000 * 1));
}

//Closes game window upon receiving a request to close to game window.
void Game::closeEvent(){ 
    if(this -> ev.type == sf::Event::Closed){this -> gameWindow -> close();}
}

// Calculate the damage of the pokemon
float Game::calcDmg(PokemonBase AtkPoke, PokemonBase DefPoke, Attack Attack){ 
    std::string AtkType = Attack.getType(); // type of attack
    std::string DefType = DefPoke.getType(); // type of defending pokemon
    float floatAtk = AtkPoke.getAtk();
    float floatDef = DefPoke.getDef();
    float floatAttackPower = Attack.getPower()/4;
    attackDamage = (floatAtk/floatDef) * floatAttackPower;

    if (AtkType == "Water" && DefType == "Fire" || AtkType == "Fire" && DefType == "Grass" || AtkType == "Grass" && DefType == "Water"){
        attackDamage = attackDamage*1.5; //super effect
   } else if((AtkType == "Fire" && DefType == "Fire" || AtkType == "Water" && DefType == "Water" || AtkType == "Grass" && DefType == "Grass")){
        attackDamage = attackDamage/2; // weak
    }
    if(attackDamage <= 0){
        std::cout << "\n Stats cannot go any lower \n";
        return 5;
    } else if(attackDamage > 40){
        return 40; // can't do too much dmg or too little
    }
    else{
        return attackDamage;
    }
    
}


//Covers the effects of key presses depending on the current phase of the game.
void Game::buttonEvent(){
    //Triggers if a key is released.
    if (this -> ev.type == sf::Event::KeyReleased || currentMenu == 4){
        int tempID; //Will be used later
        //Checks the current menu; 0 = main menu, 1 = in game, 2 = how to play, 3 = pokemon movement phase.
        switch (currentMenu){
            case 0: {
            //In main menu, allows movement between menu items, and activating menu items.
                switch(this -> ev.key.code){
                    case sf::Keyboard::Down:
                        mainMenu.moveDown();
                        break;
                    case sf::Keyboard::Up:
                        mainMenu.moveUp();
                        break;
                    case sf::Keyboard::Z:

                switch(mainMenu.getPressedIten()){
                    case 0:
                        currentMenu = 1; //Activating 'new game' switches game phase to 1 (in game).
                        break;
                    case 2:
                        currentMenu = 2; //Activating 'how to play' switches game phase to 2 (explains how to play).
                        break;
                    case 3:
                        this -> gameWindow -> close(); //Activating 'exit' causes game window to close.
                        break;
                    default:
                        break;
                }
                default:
                    break;
            }
            break;}
            case 1: {//Ingame, allows movement of cursor along game grid and selection of pokemon.
            switch(ev.key.code){
                //Keyboard presses corresponds to movement on grid.
                case sf::Keyboard::Up:
                sBoard.cursorUp();
                break;
                case sf::Keyboard::Down:
                sBoard.cursorDown();
                break;
                case sf::Keyboard::Left:
                sBoard.cursorLeft();
                break;
                case sf::Keyboard::Right:
                sBoard.cursorRight();
                break;
                case sf::Keyboard::Z:
                //test if the cursor is accessing the correct Pokemon
                if(sBoard.getTile(sBoard.cursorX/150, sBoard.cursorY/150).getPokemon().getID() != 0){
                    sBoard.getTile(sBoard.cursorX/150, sBoard.cursorY/150).getPokemon().printStats();
                }
                movesLeft = 3;
                currentMenu = 3;
                break;
                default:
                    break;
                }
            break;}
            case 3: {//Ingame, allows movement of pokemon along game grid.
            int startX = sBoard.cursorX / 150; //Sets start X to equal the horizontal position in tiles.
            int startY = sBoard.cursorY / 150; //Sets start Y to equal the vertical position in tiles.
            int endX = startX; //Sets endX to equal the horizontal position in tiles.
            int endY = startY; //Sets endY to equal the vertical position in tiles.
            switch(ev.key.code){
                case sf::Keyboard::Up:
                if(sBoard.getTile(startX, startY - 1).getPokemon().getID() == 0 && movesLeft != 0){
                    endY = startY - 1; //Shifts endY position up by 1 tile.
                    sBoard.cursorUp(); //Shifts the cursor up by 1 tile.
                    sBoard.getTile(endX, endY).setPokemon(sBoard.getTile(startX, startY).getPokemon());
                    //Retrieves the tile being shifted to, and creates a pokemon there identical to the previous pokemon.
                    sBoard.getTile(startX, startY).setPokemon(PokemonBase());
                    //Sets the pokemon on the original tile to default/null.
                    //Decrements number of moves once.
                    if (count == 1){
                        movesLeft--;
                    }else{
                        currentMenu = 1;
                    }
                    //movesLeft--;
                    std::cout<<"Moves Remaining: "<<movesLeft<<std::endl;
                }
                break;
                case sf::Keyboard::Down: //Similar to comments above but for moving Down
                if(sBoard.getTile(startX, startY + 1).getPokemon().getID() == 0 && movesLeft != 0){
                    endY = startY - 1;
                    sBoard.cursorDown();
                    sBoard.getTile(endX, endY).setPokemon(sBoard.getTile(startX, startY).getPokemon());
                    sBoard.getTile(startX, startY).setPokemon(PokemonBase());
                    if (count == 1){
                        movesLeft--;
                    }else{
                        currentMenu = 1;
                    }
                    //movesLeft--;
                    std::cout<<"Moves Remaining: "<<movesLeft<<std::endl;
                }
                break;
                case sf::Keyboard::Left: //Move left 
                if(sBoard.getTile(startX - 1, startY).getPokemon().getID() == 0 && movesLeft != 0){
                    endY = startY - 1;
                    sBoard.cursorLeft();
                    sBoard.getTile(endX, endY).setPokemon(sBoard.getTile(startX, startY).getPokemon());
                    sBoard.getTile(startX, startY).setPokemon(PokemonBase());
                    if (count == 1){
                        movesLeft--;
                    }else{
                        currentMenu = 1;
                    }
                    //movesLeft--;
                    std::cout<<"Moves Remaining: "<<movesLeft<<std::endl;
                }
                break;
                case sf::Keyboard::Right: //Move right
                if(sBoard.getTile(startX + 1, startY).getPokemon().getID() == 0 && movesLeft != 0){
                    endY = startY + 1;
                    sBoard.cursorRight();
                    sBoard.getTile(endX, endY).setPokemon(sBoard.getTile(startX, startY).getPokemon());
                    sBoard.getTile(startX, startY).setPokemon(PokemonBase());
                    if (count == 1){
                        movesLeft--;
                    }else{
                        currentMenu = 1;
                    }
                    //movesLeft--;
                    std::cout<<"Moves Remaining: "<<movesLeft<<std::endl;
                }
                break;
                //If player cancels movement.
                case sf::Keyboard::X: 
                    //Retrieves tile before movement, and sets the pokemon back there.
                    sBoard.getTile(startX, startY).setPokemon(sBoard.getTile(endX, endY).getPokemon());
                    currentMenu = 1; //Sets game phase back to 1; selection.
                    //Switches turns.
                    p1Turn = !p1Turn;
                    tempp1Turn = p1Turn;
                    break;
                case sf::Keyboard::Z:{
                    tempID = (sBoard.getTile(endX, endY).getPokemon().getID()); // gets pokemon on tiles ID
                    // with ID pass into new function to return specific pokemon
                    //After pressing Z, a pokemon is selected to be moved.
                    //The code below retrieves the stats of the pokemon and stores it in variable 'tempID'.
                    //Then, it sets the pokemon on the tile to null.
                    if (count == 0 && p1Turn == true){
                        if(tempID == 1){tempPokemon = sBoard.Bulb1;}
                        if(tempID == 2){tempPokemon = sBoard.Turt1;} 
                        if(tempID == 3){tempPokemon = sBoard.Char1;} 
                        if(tempID == 4){tempPokemon = sBoard.Torc1;}
                        if(tempID == 5){tempPokemon = sBoard.Squi1;}
                        if(tempID == 6){tempPokemon = sBoard.Osha1;} 
                        sBoard.tiles[sBoard.cursorX/150][sBoard.cursorY/150] = new Tile(sBoard.cursorX/150, sBoard.cursorY/150, PokemonBase());    
                    }

                    if (count == 0 && p1Turn == false){
                        if(tempID == 1){tempPokemon = sBoard.Bulb2;}
                        if(tempID == 2){tempPokemon = sBoard.Turt2;} 
                        if(tempID == 5){tempPokemon = sBoard.Squi2;}
                        if(tempID == 3){tempPokemon = sBoard.Char2;} 
                        if(tempID == 4){tempPokemon = sBoard.Torc2;}
                        if(tempID == 6){tempPokemon = sBoard.Osha2;} 
            
                    }
                    
                    //If the pokemon on the location after movements belongs to player 1;
                    //If it isn't player 1's turn, set tempPokemon to null pokemon.
                    //Else, set the tile the cursor is currently hovering to contain null pokemon.
                    if (sBoard.getTile(endX, endY).getPokemon().playerNo == 1){
                        if (p1Turn == false){
                            tempPokemon = PokemonBase();
                        }else{
                            sBoard.tiles[sBoard.cursorX/150][sBoard.cursorY/150] = new Tile(sBoard.cursorX/150, sBoard.cursorY/150, PokemonBase());
                        }
                    }
                    //If the pokemon on the location after movement belongs to player 2;
                    //If it is player 1's turn, set tempPokemon to null pokemon.
                    //Else, set the tile the cursor is currently hovering to contain null pokemon.
                    if (sBoard.getTile(endX, endY).getPokemon().playerNo == 2){
                        if (p1Turn == true){
                            tempPokemon = PokemonBase();
                        }else{
                            sBoard.tiles[sBoard.cursorX/150][sBoard.cursorY/150] = new Tile(sBoard.cursorX/150, sBoard.cursorY/150, PokemonBase());
                        }
                    }
                    
                    //If the tile under the cursor is empty and count == 1;
                    //Create a new tile with the contents in 'tempPokemon'.
                    //Draw on the game window the sprite belonging to the pokemon on the tile under the cursor.
                    //Then, set count to 0, set tempPokemon to null, and reset cursor location to top left (0,0).
                    if (sBoard.getTile(sBoard.cursorX/150, sBoard.cursorY/150).isEmpty == true && count == 1){// we make a new tile with the same original pokemon at a new place?
                        sBoard.tiles[sBoard.cursorX/150][sBoard.cursorY/150] = new Tile(sBoard.cursorX/150, sBoard.cursorY/150, tempPokemon); // not sure why this is broken, if u change temp to any specific pokemon it works
                        this -> gameWindow -> draw(sBoard.getTile(sBoard.cursorX/150, sBoard.cursorY/150).getPokemon().getSprite(sBoard.cursorX/150, sBoard.cursorY/150));
                        count = 0;
                        tempPokemon = PokemonBase();
                        tempX = sBoard.cursorX/150;
                        tempY = sBoard.cursorY/150;
                        sBoard.cursorX = 0;
                        sBoard.cursorY = 0;
                                
                    //If the code above fails to trigger and 'tempPokemon' contains a pokemon, increment count.
                    }else if(tempPokemon.getID() > 0) {
                        count++;
                    }
                    //Check if there is a nearby pokemon; if so, set currentMenu to 4.
                    bool enemyPokemonNearby = (sBoard.isPieceNearby(endX,endY, p1Turn));
                    if(enemyPokemonNearby == true){
                        //Initiates battlephase.
                        currentMenu = 4;
                        //Sets initial values of battlephase.
                        int currentTurn = 0;
                    }
                    break;}
                default:
                    break;
                }
            break;
            }
            case 4:{
                playerMoveChoice = 0; //Reset player move selection.
                std::cout<<"- - - NEW TURN - - -"<<std::endl;

                if(currentTurn % 2 == 0){
                    //Applies status condition effects.
                    sBoard.allyPoke.applyStatusPoison(); //Deals damage.
                    sBoard.allyPoke.applyStatusBurn(); //Deals damage, modifies stats.
                    sBoard.allyPoke.applyStatusWhirl(); //Deals damage, modifies stats.
                    sBoard.allyPoke.applyStatusBleed(); //Deals damage, modifies stats.
                    sBoard.enemyPoke.updateCHP(sBoard.allyPoke.applyStatusLeech()); //Deals damage, heals for damage dealt.
                    if(sBoard.allyPoke.applyStatusParalysis()){goto paralysisEffect0;} //Skips 1 turn if paralysis triggers.

                    //Displays move and move selection until user inputs valid move.
                    while(playerMoveChoice < 1 || playerMoveChoice > 5){
                        std::cout << "\n"<<sBoard.allyPoke.pName << " moves are:";
                        sBoard.allyPoke.printMoveset();
                        std::cout<<"Select a move from 1 to 4: ";
                        std::cin>>playerMoveChoice;
                        std::cout << std::endl;
                    }
                    
                    //Damaging attack 1.
                    if(playerMoveChoice == 1){
                        move = sBoard.allyPoke.getMove(0);  
                        float dmg = (calcDmg(sBoard.allyPoke, sBoard.enemyPoke, move));
                        std::cout << sBoard.allyPoke.pName << " used " << move.aName << " on " << sBoard.enemyPoke.pName << std::endl;
                        sBoard.enemyPoke.updateCHP(dmg);
                    }
                    //Damaging attack 2.
                    if(playerMoveChoice == 2){
                        move = sBoard.allyPoke.getMove(1);  
                        float dmg = (calcDmg(sBoard.allyPoke, sBoard.enemyPoke, move));
                        std::cout << sBoard.allyPoke.pName << " used " << move.aName << " on " << sBoard.enemyPoke.pName << std::endl;
                        sBoard.enemyPoke.updateCHP(dmg);}
                    //Status attack 1 (debuff and buff).
                    if(playerMoveChoice == 3){ move = sBoard.allyPoke.getMove(2);
                    // These are the particular stat buffs
                        if (move.buffNo == 1){sBoard.allyPoke.updateAtk(sBoard.allyPoke.getAtk()*0.25);}
                        else if(move.buffNo == 2){sBoard.allyPoke.updateDef(sBoard.allyPoke.getDef()*0.25);}
                        else if(move.buffNo == 3){sBoard.enemyPoke.updateAtk(-(sBoard.enemyPoke.getAtk()*0.25));}
                        else if(move.buffNo == 4){sBoard.enemyPoke.updateDef(-(sBoard.enemyPoke.getDef()*0.25));}
                    }
                    //Status attack 2 (apply condition).
                    if(playerMoveChoice == 4){
                        move = sBoard.allyPoke.getMove(3); //Obtains status move and stores it in 'move'.
                        //Obtains the status applied by 'move' and inputs it into the modifyStatus function.
                        //The modifyStatus function contains a list of conditions. If an input condition matches one 
                        //on the list, that condition is set to true.
                        std::cout << sBoard.allyPoke.pName << " used " << move.aName << " on " << sBoard.enemyPoke.pName << std::endl;
                        sBoard.enemyPoke.modifyStatus(move.getStatusApplied());      
                    }
                    if (sBoard.enemyPoke.getCHP() <= 0){std::cout<< sBoard.enemyPoke.pName << " has: 0 health left."<<std::endl;}
                    else{std::cout<< sBoard.enemyPoke.pName << " has: "<<sBoard.enemyPoke.getCHP()<<" health left."<<std::endl;}
                    //Set turn order.
                    paralysisEffect0: 
                    currentTurn++;
                }
                else if(currentTurn % 2 == 1){
                    //Applies status condition effects.
                    sBoard.enemyPoke.applyStatusPoison(); //Deals damage.
                    sBoard.enemyPoke.applyStatusBurn(); //Deals damage, modifies stats.
                    sBoard.enemyPoke.applyStatusWhirl(); //Deals damage, modifies stats.
                    sBoard.enemyPoke.applyStatusBleed(); //Deals damage, modifies stats.
                    sBoard.allyPoke.updateCHP(sBoard.enemyPoke.applyStatusLeech()); //Deals damage, heals for damage dealt.
                    if(sBoard.enemyPoke.applyStatusParalysis()){goto paralysisEffect1;} //Skips 1 turn if paralysis triggers.
                    //Displays move and move selection until user inputs valid move.
                    while(playerMoveChoice < 1 || playerMoveChoice > 5){
                        std::cout <<"\n"<< sBoard.enemyPoke.pName << " moves are:";
                        sBoard.enemyPoke.printMoveset();
                        std::cout<<"Select a move from 1 to 4: ";
                        std::cin>>playerMoveChoice;
                        std::cout << std::endl;
                    }

                    //Damaging attack 1.
                    if(playerMoveChoice == 1){
                        move = sBoard.enemyPoke.getMove(0);  
                        float dmg = (calcDmg(sBoard.enemyPoke, sBoard.allyPoke, move));
                        std::cout << sBoard.enemyPoke.pName << " used " << move.aName << " on " << sBoard.allyPoke.pName << std::endl;
                        sBoard.allyPoke.updateCHP(dmg);}
                    //Damaging Attack 2.
                    if(playerMoveChoice == 2){
                        move = sBoard.enemyPoke.getMove(1);  
                        float dmg = (calcDmg(sBoard.enemyPoke, sBoard.allyPoke, move));
                        std::cout << sBoard.enemyPoke.pName << " used " << move.aName << " on " << sBoard.allyPoke.pName << std::endl;
                        sBoard.allyPoke.updateCHP(dmg);}
                    //Status attack 1 (apply condition).
                    if(playerMoveChoice == 3){
                        move = sBoard.enemyPoke.getMove(2); 
                        if (move.buffNo == 1){sBoard.enemyPoke.updateAtk(sBoard.enemyPoke.getAtk()*0.25);}
                        else if(move.buffNo == 2){sBoard.enemyPoke.updateDef(sBoard.enemyPoke.getDef()*0.25);}
                        else if(move.buffNo == 3){sBoard.allyPoke.updateAtk(-(sBoard.allyPoke.getAtk()*0.25));}
                        else if(move.buffNo == 4){sBoard.allyPoke.updateDef(-(sBoard.allyPoke.getDef()*0.25));}
                    }
                    //Status attack 2 (apply condition).
                    if(playerMoveChoice == 4){
                        move = sBoard.enemyPoke.getMove(3); //Obtains status move and stores it in 'move'.
                        //Obtains the status applied by 'move' and inputs it into the modifyStatus function.
                        //The modifyStatus function contains a list of conditions. If an input condition matches one 
                        //on the list, that condition is set to true.
                        std::cout << sBoard.enemyPoke.pName << " used " << move.aName << " on " << sBoard.allyPoke.pName << std::endl;
                        sBoard.allyPoke.modifyStatus(move.getStatusApplied());      
                    }
                    if (sBoard.allyPoke.getCHP() < 0){std::cout<< sBoard.allyPoke.pName << " has: 0 health left."<<std::endl;}
                    else{std::cout<< sBoard.allyPoke.pName << " has: "<<sBoard.allyPoke.getCHP()<<" health left."<<std::endl;}
                    //Set turn order.
                    paralysisEffect1:
                    currentTurn++;
                }
                //Swaps Turns
                p1Turn = !p1Turn;

                //If ally health reaches 0, destroy it and end combat phase.
                if(sBoard.allyPoke.getCHP() <= 0){
                    std::cout << sBoard.enemyPoke.pName << " wins" << std::endl;
                    std::cout << "Fight over!" <<std::endl;
                    // If the ally pokemon dies the win counter of the enemy will increase;
                    if (sBoard.allyPoke.playerNo == 1){winCountp2++;}
                    else if (sBoard.allyPoke.playerNo == 2){winCountp1++;}
                    if(winCountp2 == 6){
                        std::cout << "\n Winner is p2 \n";
                        howToPlay.setString("Player 2 wins");
                        howToPlay.setFillColor(sf::Color::Blue);
                        howToPlay.setPosition(sf::Vector2f(1430, 400 * 1));
                    }else if(winCountp1 == 6){
                        std::cout << "\n Winner is p1 \n";
                        howToPlay.setString("Player 1 wins");
                        howToPlay.setFillColor(sf::Color::Blue);
                        howToPlay.setPosition(sf::Vector2f(1430, 400 * 1));
                    }
                    sBoard.allyPoke = PokemonBase(); //Clear the pokemon.
                    //End Combat Phase
                    currentMenu = 1;
                    sBoard.tiles[tempX][tempY] = new Tile(tempX, tempY, PokemonBase()); 
                    this -> gameWindow -> draw(sBoard.getTile(tempX, tempY).getPokemon().getSprite(tempX, tempY));
                }
                //If enemy health reaches 0, destroy it and end combat phase.å
                if(sBoard.enemyPoke.getCHP() <= 0){
                    std::cout << sBoard.allyPoke.pName << " wins"<<std::endl;
                    std::cout << "Fight over!" <<std::endl;
                    // counters for winners
                    if (sBoard.enemyPoke.playerNo == 1){winCountp2++;}
                    else if (sBoard.enemyPoke.playerNo == 2){winCountp1++;}
                    if(winCountp2 == 6){
                        std::cout << "\n Winner is p2 \n";
                        howToPlay.setString("Player 2 wins");
                        howToPlay.setFillColor(sf::Color::Blue);
                        howToPlay.setPosition(sf::Vector2f(1430, 400 * 1));
                    }else if(winCountp1 == 6){
                        std::cout << "\n Winner is p1 \n";
                        howToPlay.setString("Player 1 wins");
                        howToPlay.setFillColor(sf::Color::Blue);
                        howToPlay.setPosition(sf::Vector2f(1430, 400 * 1));
                    }
                    sBoard.enemyPoke = PokemonBase(); //Clear the pokemon
                    //End Combat Phase
                    currentMenu = 1;
                    if (tempp1Turn == true){
                        sBoard.tiles[tempX+ 1 ][tempY] = new Tile(tempX + 1, tempY, PokemonBase()); 
                        this -> gameWindow -> draw(sBoard.getTile(tempX + 1, tempY).getPokemon().getSprite(tempX +1, tempY));
                    }else if (tempp1Turn == false){
                        sBoard.tiles[tempX- 1 ][tempY] = new Tile(tempX - 1, tempY, PokemonBase()); 
                        this -> gameWindow -> draw(sBoard.getTile(tempX - 1, tempY).getPokemon().getSprite(tempX -1, tempY));
                    }   
                }
                break;}
                default:
                    break;
        }
    } 
}
// these functions make it easier to use lets say after a move u can call this function to change atk,def of either pokemon
// easily, also x 1.5 and * 0.75 are fair and simple
void incAtkAlly(PokemonBase AtkPoke){AtkPoke.cAtk = AtkPoke.cAtk * 1.5;}
void incDefAlly(PokemonBase AtkPoke){AtkPoke.cDef = AtkPoke.cDef * 1.5;}
void defAtkEnemy(PokemonBase DefPoke){DefPoke.cAtk = DefPoke.cAtk * 0.75;}
void defDefEnemy(PokemonBase DefPoke){DefPoke.cDef = DefPoke.cDef * 0.75;}  

void Game::eventControl(){
    //Loop activates as long as an event (keypress, mouse movement, etc) has occured.
    while(this -> gameWindow -> pollEvent(this -> ev)){
        closeEvent(); //Closes the game window upon request to close the game window.
        buttonEvent(); //Covers the effects of key presses depending on the current phase of the game.
    }
}
void Game::update(){ 
    this-> eventControl(); 
}
void Game::render(){
    this -> gameWindow -> clear(); //Wipes previous frame.
    gameWindow -> draw(buttonControls); //Gamewindow always displays keybinds.
    loadMap();
    switch (currentMenu){ //Checks the current phase of the game.
        case 0: //If [main menu], sets current frame to the main menu.
        mainMenu.drawMenu(*this -> gameWindow);
        break;
        case 1: //If [pokemon selection], sets current frame to game (select a pokemon).
        gameWindow -> draw(sBoard.getCursor());
        case 2: //If [how to play], sets current frame to display instructions on how to play the game.
        gameWindow -> draw(howToPlay);
        break;
        case 3: //If [], . (not sure what this is; pokemon movement phase?)
        gameWindow -> draw(sBoard.getCursor());
        break;
    }
    this -> gameWindow -> display(); //Displays the current frame.
}
Game::~Game(){delete this -> gameWindow;}


                