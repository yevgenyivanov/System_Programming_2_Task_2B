#include "card.hpp"
#include <iostream>
Card::Card(int value, std::string suit){
    this->value = value;
    this->suit = suit;
}

int Card::getCardValue(){
    return this->value;
}
std::string Card::getCardSuit(){
    return this->suit;
}


void Card::printCard(){
    std::cout<< this->value << std::endl;
}


int Card::compareCards(Card other){
    //equal values
    if(this->value == other.getCardValue()){
        return 0;
    }
    //this card is stronger than the other
    else if(this->value > other.getCardValue()){

        //Ace beats everything other than 2
        if(this->value == 2 && other.getCardValue() == 1) return 1;
        if(this->value != 2 && other.getCardValue() == 1) return -1; 
        
        //default return
        return 1;
        
    }
    //other is stronger than this
    else{
        //Ace beats everything other than 2
        if(this->value == 1 && other.getCardValue() != 2) return 1;
        if(this->value == 1 && other.getCardValue() == 2) return -1;
        
        //default return
        return -1;
    }
}