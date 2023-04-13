#include <iostream>
#include "card.hpp"

using namespace std;
using namespace ariel;

Card::Card(){}

Card::Card(int val, string type){
    this->value=val;
    this->type=type;
}

//copy constructor
Card::Card(const Card& other) {
    value = other.value;
    type = other.type;
}

//copy assignment operator
Card& Card::operator=(const Card& other) {
    if (this != &other) { // check for self-assignment
        value = other.value;
        type = other.type;
    }
    return *this;
}

//move constructor
Card::Card(Card&& other) noexcept {
    value = other.value;
    type = move(other.type);
    other.value = 0;
    // other.type is automatically set to empty string
}

//move assignment operator
Card& Card::operator=(Card&& other) noexcept {
    if (this != &other) { // check for self-assignment
        value = other.value;
        type = move(other.type);
        other.value = 0;
        // other.type is automatically set to empty string
    }
    return *this;
}

Card::~Card(){

}

int Card::getValue(){
    return value;
}

string Card::getType(){
    return type;
}
