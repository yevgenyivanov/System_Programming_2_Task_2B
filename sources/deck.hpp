#pragma once

#include "card.hpp"
#include <array>
constexpr int deckSize = 52;
constexpr int ace = 1;
constexpr int two = 2;
constexpr int three = 3;
constexpr int four = 4;
constexpr int five = 5;
constexpr int six = 6;
constexpr int seven = 7;
constexpr int eight = 8;
constexpr int nine = 9;
constexpr int ten = 10;
constexpr int jack = 11;
constexpr int queen = 12;
constexpr int king = 13;
// #include "card.cpp"
class Deck{
    private:
        
        std::array<Card, deckSize> gameDeck = {
            /*
            1:      Ace
            2 - 10: Numbers
            11:     Jack
            12:     Queen
            13:     King
            */

            //Diamonds
            Card (ace, "Ace of Diamonds"),
            Card (two, "2 of Diamonds"),
            Card (three, "3 of Diamonds"),
            Card (four, "4 of Diamonds"),
            Card (five, "5 of Diamonds"),
            Card (six, "6 of Diamonds"),
            Card (seven, "7 of Diamonds"),
            Card (eight, "8 of Diamonds"),
            Card (nine, "9 of Diamonds"),
            Card (ten, "10 of Diamonds"),
            Card (jack, "Jack of Diamonds"),
            Card (queen, "Queen of Diamonds"),
            Card (king, "King of Diamonds"),

            //Clubs
            Card (ace, "Ace of Clubs"),
            Card (two, "2 of Clubs"),
            Card (three, "3 of Clubs"),
            Card (four, "4 of Clubs"),
            Card (five, "5 of Clubs"),
            Card (six, "6 of Clubs"),
            Card (seven, "7 of Clubs"),
            Card (eight, "8 of Clubs"),
            Card (nine, "9 of Clubs"),
            Card (ten, "10 of Clubs"),
            Card (jack, "Jack of Clubs"),
            Card (queen, "Queen of Clubs"),
            Card (king, "King of Clubs"),
            
            //Hearts
            Card (ace, "Ace of Hearts"),
            Card (two, "2 of Hearts"),
            Card (three, "3 of Hearts"),
            Card (four, "4 of Hearts"),
            Card (five, "5 of Hearts"),
            Card (six, "6 of Hearts"),
            Card (seven, "7 of Hearts"),
            Card (eight, "8 of Hearts"),
            Card (nine, "9 of Hearts"),
            Card (ten, "10 of Hearts"),
            Card (jack, "Jack of Hearts"),
            Card (queen, "Queen of Hearts"),
            Card (king, "King of Hearts"),
            
            //Spades
            Card (ace, "Ace of Spades"),
            Card (two, "2 of Spades"),
            Card (three, "3 of Spades"),
            Card (four, "4 of Spades"),
            Card (five, "5 of Spades"),
            Card (six, "6 of Spades"),
            Card (seven, "7 of Spades"),
            Card (eight, "8 of Spades"),
            Card (nine, "9 of Spades"),
            Card (ten, "10 of Spades"),
            Card (jack, "Jack of Spades"),
            Card (queen, "Queen of Spades"),
            Card (king, "King of Spades")
            
        };

        public: 
            Deck();
            // ~Deck();
            void printDeck();
            void shuffleDeck();
            Card getCard(int);
            
};