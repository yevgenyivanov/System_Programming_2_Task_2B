#include "game.hpp"
#include "player.hpp"
#include "card.hpp"
#include <iostream>
#include <string>

// constructor
Game::Game(Player &playerA, Player &playerB) : playerA(playerA), playerB(playerB)
{
    // //check if the player is the same player
    // if(playerA.is_same(playerB)){
    //     // std::cout<< "Solo playing is not permitted. Aborting." << std::endl;
    //     throw std::invalid_argument("Solo playing is not permitted. Aborting.");
    // }

    // check if one of the players is still playing in a different game, therefore cannot start another one.
    if (playerA.getIsPlaying() || playerB.getIsPlaying()){
        // std::cout<< "One of the players is not finished with another game. Try again later." << std::endl;
        throw std::runtime_error("One of the players is not finished with another game. Try again later.");
        // return;
    }
        

    //set playerA playerB to playing status, prevent errors with other games that the player may want to participate in.
    playerA.setPlayerStatus(true);
    playerB.setPlayerStatus(true);

    //deck is created unshuffled(for testing purposes)
    this->_deck.shuffleDeck();
    
    this->playerA_deckPointer = 25; // player A 25-0  range of _deck
    this->playerB_deckPointer = 51; // player B 51-26 range of _deck
    //keep track of total turns
    this->turnCounter = 0;
    //keep track of total draws
    this->tieAmount = 0;
    
    this->playerA_cardsWon = 0;
    this->playerB_cardsWon = 0;
    //clear turnLog[] of memory junk that could possibly be there
    for (int i = 0; i < 26; i++)
    {
        this->turnLog.at((unsigned long)i) = "";
    }

    //each player is dealt 26 cards
    playerA.setStackSize(26);
    playerB.setStackSize(26);
}

// helper functions
void Game::addTurnToLog(std::string turn)
{
    this->turnLog.at((unsigned long)this->turnCounter - 1) = turn + " \n";
}


void Game::printLastTurn()
{
    //prevent out of bounds errors
    if(this->turnCounter == 0){
        std::cout<< "No round has been played yet. No turn/s to print. Returning." << std::endl;
        return;
    }
    std::cout << this->turnLog.at((unsigned long)this->turnCounter - 1) << std::endl;
    return;
}


void Game::reducePlayerStack(Player &player)
{
    player.setStackSize(player.stacksize() - 1);
    return;
}

//decrement deck pointers and reduce stack size for each player, as well as increment the turn no.
void Game::decrementCardPs_incrementTurn(){
    this->playerA_deckPointer--;
    this->playerB_deckPointer--;
    reducePlayerStack(playerA);
    reducePlayerStack(playerB);
    this->turnCounter++;
    //players finished playing the game
    return;

}

void Game::endGameCheck(){
    //check that end game is really the endgame using all pointers and player values:
    if(
        ((this->playerA_deckPointer == -1 && this->playerB_deckPointer == 25) || this->turnCounter >= 26)) //pointers and turn amount reached max values
         //players ran out of cards
        {
            // int negateCards = playerA.cardesTaken();
            //zero everything
            playerA.setStackSize(0);
            
            // playerA.addCards(-negateCards);
            playerA.setPlayerStatus(false);
            
            // negateCards = playerB.cardesTaken();
            playerB.setStackSize(0);
            // playerB.addCards(-negateCards);
            playerB.setPlayerStatus(false);
        }
    
        
}

 
    
void Game::playerStatCalculator(Player &player) {
    double winrate = (double)(player.cardesTaken()) / this->turnCounter;
    std::cout<< "Player: " << player.getName() << std::endl 
    <<  "Cards Won: "<< player.cardesTaken()<< std::endl
    <<  "Cards Played: "<< this->turnCounter << std::endl
    << "Win Rate: " << (double)winrate << std::endl;
    return;
}

void Game::postGameStatCalculator(){
    double winrate = (double)(this->playerA_cardsWon) / this->turnCounter;
    std::cout<< "Player: " << playerA.getName() << std::endl 
    <<  "Cards Won: "<< this->playerA_cardsWon<< std::endl
    <<  "Cards Played: "<< this->turnCounter << std::endl
    << "Win Rate: " << (double)winrate << std::endl;


    std::cout<< "------------" << std::endl;


    winrate = (double)(this->playerB_cardsWon) / this->turnCounter;
    std::cout<< "Player: " << playerB.getName() << std::endl 
    <<  "Cards Won: "<< this->playerB_cardsWon<< std::endl
    <<  "Cards Played: "<< this->turnCounter << std::endl
    << "Win Rate: " << (double)winrate << std::endl;
    return;
}


std::string Game::turn_toString(std::string cardSuit_A, std::string cardSuit_B){
    return "Turn no. " + std::to_string(this->turnCounter) + ": "
                             + playerA.getName() + " played: " + cardSuit_A + " | \t"
                             + playerB.getName() + " played: " + cardSuit_B;
}

std::string Game::faceDown_toString(){
    return "Turn no. " + std::to_string(this->turnCounter) + ": "
                                 + playerA.getName() + " played a card face down" + "\t" 
                                 + playerB.getName() + " played a card face down";
}



void Game::drawFaceDown()
{
    // card drawing and deck management like in playTurn()
    Card playerA_DrawnCard = this->_deck.getCard(this->playerA_deckPointer);
    Card playerB_DrawnCard = this->_deck.getCard(this->playerB_deckPointer);
    decrementCardPs_incrementTurn();
    // create string with cards that were played face down
    std::string faceDownCards = faceDown_toString();
    //log turn
    addTurnToLog(faceDownCards);
}



void Game::tieResolver()
{
    //check if final round ended on a tie in playTurn() without a tie loop before (tie loop would be handled below in the while() loop)
    if(this->playerA_deckPointer == -1 && this->playerB_deckPointer == 25){
        //if final round was face down draw
        if(this->turnLog.at((unsigned long)25).find("face down")){
            //give each player 2 cards, one for face up draw in turn 25, one for face down draw in turn 26
            playerA.addCards(2);
            playerB.addCards(2);
            return;
        }
        else if(this->turnLog.at((unsigned long)25).find("This turn is a tie.")){
            //give each player 1 card. 
            playerA.addCards(1);
            playerB.addCards(1);
            this->turnLog.at((unsigned long)25) += "|| Final game round is a tie.";
            return;
        }
        // else something went wrong
        else{
            std::abort();
        }
    }

    // winner gets 6+ loopCounter*4 cards (for each additional tie that is played in a row)
    int loopCounter = 0, winAmnt = 6 + (4*loopCounter);
    this->tieAmount++;
    // draw card face up (face down draw was played in playTurn() before going to this method)
    Card playerA_DrawnCard = this->_deck.getCard(this->playerA_deckPointer);
    Card playerB_DrawnCard = this->_deck.getCard(this->playerB_deckPointer);
    decrementCardPs_incrementTurn();
    std::string currentTurn = turn_toString(playerA_DrawnCard.getCardSuit(), playerB_DrawnCard.getCardSuit());


    // compare current draw after tie round, same as in playTurn()
    //playerA wins comparison
    if (playerA_DrawnCard.compareCards(playerB_DrawnCard) == 1)
    {
        playerA.addCards(winAmnt);
        currentTurn += " || " + playerA.getName() + " wins this turn.";
        addTurnToLog(currentTurn);

        return;
    }

    // playerB wins comparison
    else if (playerA_DrawnCard.compareCards(playerB_DrawnCard) == -1)
    {
        playerB.addCards(winAmnt);
        currentTurn += " || " + playerB.getName() + " wins this turn.";
        addTurnToLog(currentTurn);

        return;
    }
    // additional tie, this->tieAmount not incremented as it will be incremented in while loop below.
    else{
        currentTurn += " || This turn is a tie.";
        addTurnToLog(currentTurn);
        //no return to keep checking if next turn is another tie
    }

    // while loop for comparison:
    while (playerA_DrawnCard.compareCards(playerB_DrawnCard) == 0 && // while card drawing leads to a tie
    (this->playerA_deckPointer >=0 && this->playerB_deckPointer>=26)) // prevent out of bounds error if final draw is a tie as well
    {
        loopCounter ++;
        this->tieAmount++;
        // draw a card face down, as stated in rules
        drawFaceDown();
        // draw a card face up
        playerA_DrawnCard = this->_deck.getCard(this->playerA_deckPointer);
        playerB_DrawnCard = this->_deck.getCard(this->playerB_deckPointer);
        decrementCardPs_incrementTurn();
        // log turn
        currentTurn = turn_toString(playerA_DrawnCard.getCardSuit(), playerB_DrawnCard.getCardSuit());
        
        
        
        // card comparison
        // playerA wins comparison
        if (playerA_DrawnCard.compareCards(playerB_DrawnCard) == 1)
        {
            playerA.addCards(winAmnt);
            currentTurn += " || " + playerA.getName() + " wins this turn.";
            addTurnToLog(currentTurn);

            return;
        }

        // playerB wins comparison
        else if (playerA_DrawnCard.compareCards(playerB_DrawnCard) == -1)
        {
            playerB.addCards(winAmnt);
            currentTurn += " || " + playerB.getName() + " wins this turn.";
            addTurnToLog(currentTurn);

            return;
        }

        // tie
        else
        {
            currentTurn += " || This turn is a tie.";
            addTurnToLog(currentTurn);
        }
    }

    //while loop ended on a tie 
    if(this->playerA_deckPointer == -1 || this->playerB_deckPointer == 25 && 
    (playerA_DrawnCard.compareCards(playerB_DrawnCard) == 0))
    {
        //each player receives half of the played cards
        playerA.addCards(winAmnt/2);
        playerB.addCards(winAmnt/2);
        
        //log end of game:
        currentTurn+= " || Final game round is a tie.";
        addTurnToLog(currentTurn);
        return;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// required functions
void Game::playTurn()
{

    //check if the player is the same player
    if(playerA.is_same(playerB)){
        // std::cout<< "Solo playing is not permitted. Aborting." << std::endl;
        throw std::invalid_argument("Solo playing is not permitted. Aborting.");
    }


    // check if game was already played to the end by deckPointer and by turnCounter
    if (this->playerA_deckPointer < 0 || this->playerB_deckPointer < 26){
        std::cout<< "Players already finished playing." << std::endl;
        // if(playerA.cardesTaken() >0) this->playerA_cardsWon = playerA.cardesTaken();
        // if(playerB.cardesTaken() >0) this->playerB_cardsWon = playerB.cardesTaken();
        // endGameCheck();
        throw std::runtime_error("Players already finished playing.");
        // return;
    }
        
    if (this->turnCounter >= 26){
        std::cout<< "Turn amount is exceeded. aborting." << std::endl;
        // if(playerA.cardesTaken() >0) this->playerA_cardsWon = playerA.cardesTaken();
        // if(playerB.cardesTaken() >0) this->playerB_cardsWon = playerB.cardesTaken();
        // endGameCheck();
        throw std::runtime_error("Turn amount exceeded.");
        // return;
    } 
        
    
    // each player draws a card from his deck using the appropriate pointer
    Card playerA_DrawnCard = this->_deck.getCard(this->playerA_deckPointer);
    Card playerB_DrawnCard = this->_deck.getCard(this->playerB_deckPointer);

    decrementCardPs_incrementTurn();

    // create string to log turn
    std::string currentTurn = turn_toString(playerA_DrawnCard.getCardSuit(), playerB_DrawnCard.getCardSuit());

    // cards comparison
    // playerA wins comparison
    if (playerA_DrawnCard.compareCards(playerB_DrawnCard) == 1)
    {
        playerA.addCards(2);
        currentTurn += " || " + playerA.getName() + " wins this turn.";
        addTurnToLog(currentTurn);
        

        return;
    }

    // playerB wins comparison
    else if (playerA_DrawnCard.compareCards(playerB_DrawnCard) == -1)
    {
        playerB.addCards(2);
        currentTurn += " || " + playerB.getName() + " wins this turn.";
        addTurnToLog(currentTurn);
        
        return;
    }

    // tie
    else
    {
        currentTurn += " || This turn is a tie.";
        addTurnToLog(currentTurn);
        // draw card face down
        drawFaceDown();
        tieResolver();
        return;
        
    }
}



void Game::playAll()
{
        //at most 26 turns per game
        if(turnCounter > 25){
            std::cout<< "No more cards left. Game is finished." << std::endl;
            throw std::runtime_error("No more cards left. Game is finished.");
            endGameCheck();
            return;
        }
        while(this->turnCounter <=25){
            playTurn();
        }
        // if(playerA.cardesTaken() >0) this->playerA_cardsWon = playerA.cardesTaken();
        // if(playerB.cardesTaken() >0) this->playerB_cardsWon = playerB.cardesTaken();
        // endGameCheck();
        return;
}
void Game::printWiner()
{
    // get cards won from playerA and playerB
    if(playerA.cardesTaken() == playerB.cardesTaken())
        std::cout<< "The game ends on a tie." << std::endl;
    else if(playerA.cardesTaken() > playerB.cardesTaken())
        std::cout<< playerA.getName() + " wins the game." << std::endl;
    else
        std::cout<< playerB.getName() + " wins the game." << std::endl;
    return;
}
void Game::printLog()
{
    for(int i=0; i<this->turnCounter; i++){
        std::cout<< this->turnLog.at((unsigned long)i);
    }
}
void Game::printStats()
{   
    // if(playerA.stacksize() > 0 && playerB.stacksize() > 0){
        playerStatCalculator(playerA);
        std::cout<< "------------" << std::endl;
        playerStatCalculator(playerB);
        std::cout<< "------------" << std::endl;
        std::cout<< "Tie Amount in Game: " << this->tieAmount<< std::endl
        << "Tie Rate: " << (double)(this->tieAmount)/ this->turnCounter<<std::endl;
        
    // }
    // else{//game is over
    //     postGameStatCalculator();
    //     std::cout<< "------------" << std::endl;
    //     std::cout<< "Tie Amount in Game: " << this->tieAmount<< std::endl
    //     << "Tie Rate: " << (double)(this->tieAmount)/ this->turnCounter<<std::endl;
    // }
    

    return;
}
