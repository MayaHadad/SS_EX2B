#include <iostream>
#include "player.hpp"

using namespace std;
using namespace ariel;

Player::Player(string name){
    this->name=name;
    this->stackSize=0;
    this->cardsTaken=0;
    this->playing=0;
}

//copy constructor
Player::Player(const Player& other) {
    name = other.name;
    stackSize = other.stackSize;
    cardsTaken=other.cardsTaken;
    playing=other.playing;
}

//copy assignment operator
Player& Player::operator=(const Player& other) {
    if (this != &other) { // check for self-assignment
        name = other.name;
        stackSize = other.stackSize;
        cardsTaken=other.cardsTaken;
        playing=other.playing;
    }
    return *this;
}

//move constructor
Player::Player(Player&& other) noexcept {
    name = move(other.name);
    stackSize = other.stackSize;
    cardsTaken = other.cardsTaken;
    playing = other.playing;
}


//move assignment operator
Player& Player::operator=(Player&& other) noexcept {
    if (this != &other) { // check for self-assignment
        name = move(other.name);
        stackSize = other.stackSize;
        cardsTaken = other.cardsTaken;
        playing = other.playing;
    }
    return *this;
}

Player::~Player(){

}

int Player::stacksize() {return this->stackSize;}

void Player::setStackSize(int size){
    if(size<=26 && size>=0) this->stackSize=size;
}

int Player::cardesTaken() {return this->cardsTaken;}

void Player::setCardsTaken(int num){
    if(num<=52 && num>=0) this->cardsTaken=num;
}

int Player::getPlaying() {return this->playing;}

void Player::setPlaying(int playing){
    if(playing==1 || playing==0) this->playing=playing;
}

string Player::getName() {return this->name;}