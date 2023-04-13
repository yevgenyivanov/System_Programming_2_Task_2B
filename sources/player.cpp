#include "player.hpp"
#include <string>
#include <iostream>
//constructor
Player::Player(std::string name){
    this->name = name;
    this->stack_size = 0;
    this->cards_won = 0;
    this->isPlaying = false; // a player is not playing a game upon initialization

}
//getters
int Player::cardesTaken(){return this->cards_won;}
int Player::stacksize(){return this->stack_size;}
bool Player::getIsPlaying(){return this->isPlaying;}
std::string Player::getName(){return this->name;}

bool Player::is_same(Player &other){return (this == &other);} //prevent solo player games


//setters
void Player::addCards(int cardAmount){this->cards_won +=cardAmount;}
void Player::setStackSize(int size){this->stack_size = size;}
void Player::setPlayerStatus(bool status){ this->isPlaying = status;}

//destructor
// Player::~Player(){delete this;}