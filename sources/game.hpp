#pragma once
#include "player.hpp"
#include "card.hpp"
#include "deck.hpp"
#include <array>
constexpr int maxTurns = 26;
class Game{

    private:
        Deck _deck;
        Player &playerA;
        Player &playerB;
        int playerA_deckPointer ; //player A gets 25-0  range of Deck[]
        int playerB_deckPointer ; //player B gets 51-26 range of Deck[]
        int turnCounter;
        int tieAmount;
        int playerA_cardsWon, playerB_cardsWon;
        std::array<std::string, maxTurns> turnLog; //at most 26 turns per game
        void endGameCheck();
    public:
        Game(Player &, Player &); //default constructor
        
        //helper functions
        void addTurnToLog(std::string);
        void drawFaceDown();
        void tieResolver();
        void playerStatCalculator(Player &);
        void postGameStatCalculator();
        void reducePlayerStack(Player &);
        std::string turn_toString(std::string, std::string);
        std::string faceDown_toString();
        void decrementCardPs_incrementTurn();
        
        //required functions
        void playTurn();
        void printLastTurn();    
        void playAll();
        void printWiner(); // *winner
        void printLog();
        void printStats();
        // int printDeckSize();

        
};

namespace ariel{
//name space funcs will go here if needed
};