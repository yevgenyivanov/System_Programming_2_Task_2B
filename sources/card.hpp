#pragma once
#include <iostream>
class Card{
    int value;
    std::string suit;

    public:
        Card(int, std::string);
        int getCardValue();
        std::string getCardSuit();
        void printCard();
        int compareCards(Card);
};