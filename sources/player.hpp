#pragma once
#include <string>
#include "card.hpp"


class Player{

    private:
        
        std::string name;
        int cards_won;
        int stack_size;
        bool isPlaying;
    public:
        Player(std::string);
        // ~Player();

        //getters
        int stacksize();
        int cardesTaken();
        bool getIsPlaying();
        std::string getName();
        bool is_same(Player &);
        //setters
        void addCards(int);
        void setStackSize(int);
        void setPlayerStatus(bool);

};