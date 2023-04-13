#include "deck.hpp"
#include "card.hpp"
// #include "card.cpp"
#include <iostream>
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

Deck::Deck(){}; // create deck
// Deck::~Deck(){delete this;} // todo deconstructor
void Deck::printDeck(){ 
    for(int i=0; i<52; i++){

        //uncomment this block to add card suits prints deck before shuffle
        // if(i==0){
        //     std::cout << "Diamonds:" << std::endl ;
        // }
        // if(i==13){
        //     std::cout << "Clubs:" << std::endl ;
        // }
        // if(i==26){
        //     std::cout << "Hearts:" << std::endl ;
        // }
        // if(i==39){
        //     std::cout << "Spades:" << std::endl ;
        // }
        this->gameDeck.at((unsigned long)i).printCard();
    }
};

void Deck::shuffleDeck(){

    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(std::begin(this->gameDeck), std::end(this->gameDeck), std::default_random_engine(seed));
}

Card Deck::getCard(int num){
    //if conditions to prevent out of bounds errors
    if(num>51) return this->gameDeck.at(51);
    if(num<0) return this->gameDeck.at(0);

    return this->gameDeck.at((unsigned long)num);
}

