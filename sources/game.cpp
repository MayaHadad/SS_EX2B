#include <iostream>
#include "player.hpp"
#include "game.hpp"
#include "card.hpp"

using namespace std;
using namespace ariel;

Game::Game(Player pl1, Player pl2)
        :player1(pl1.getName()), player2(pl2.getName()){
    if(player1.getPlaying()==1 || player2.getPlaying()==1) throw "one of the players is already playing a game";
    else if(&player1==&player2) throw "same player";

    this->player1=pl1;
    this->player2=pl2;
    this->roundNum=0;
    this->drawNum=0;
    this->winsp1=0;
    this->winsp2=0;

    //creating deck
    Card deck[52];
    string type="Hearts";
    int indx=0;
    for(int i=0; i<4; i++){
        if(i==1) type="Diamonds";
        else if(i==2) type="Spades";
        else type="Clubs";
        for(int j=2; j<=14; j++){
            Card card(j, type);
            deck[indx]=card;
            indx++;
        }
    }

    //shuffling deck
    srand(time(nullptr));
    for (int i = 0; i < fullDeck; i++)
    {
        int j=rand()%fullDeck;
        Card tmp=deck[i];
        deck[i]=deck[j];
        deck[j]=tmp;
    }

    //spliting deck
    for (int i = 0; i < fullDeck; i++)
    {
        if(i<halfDeck) this->stack1.push(deck[i]);
        else this->stack2.push(deck[i]);
    }

    player1.setPlaying(1);
    player2.setPlaying(1);
    player1.setStackSize(stack1.size());
    player2.setStackSize(stack2.size());
    player1.setCardsTaken(0);
    player2.setCardsTaken(0);
}

//copy constructor
Game::Game(const Game& other) : player1(other.player1), player2(other.player2), stack1(other.stack1), stack2(other.stack2),
                                roundNum(other.roundNum), drawNum(other.drawNum),
                                winsp1(other.winsp1), winsp2(other.winsp2) {
  for (unsigned long i = 0; i < halfDeck; i++) {
      log[i] = other.log[i];
  }
}

//copy assignment operator
Game& Game::operator=(const Game& other) {
  if (this != &other) {
      player1 = other.player1;
      player2 = other.player2;
      stack1 = other.stack1;
      stack2 = other.stack2;
      roundNum = other.roundNum;
      drawNum = other.drawNum;
      winsp1=other.winsp1;
      winsp2=other.winsp2;
      for (unsigned long i = 0; i < halfDeck; i++) {
          log[i] = other.log[i];
      }
  }
  return *this;
}

//move constructor
Game::Game(Game&& other) noexcept : player1(move(other.player1)), player2(move(other.player2)),
                                    stack1(move(other.stack1)), stack2(move(other.stack2)),
                                    roundNum(move(other.roundNum)), drawNum(move(other.drawNum)),
                                    winsp1(move(other.winsp1)), winsp2(move(other.winsp2)) {
  for (unsigned long i = 0; i < halfDeck; i++) {
      log[i] = move(other.log[i]);
  }
}

//move assignment operator
Game& Game::operator=(Game&& other) noexcept{
  if (this != &other) {
    player1=move(other.player1); 
    player2=move(other.player2);
    stack1=move(other.stack1); 
    stack2=move(other.stack2);
    roundNum=move(other.roundNum);
    drawNum=move(other.drawNum);
    winsp1=move(other.winsp1);
    winsp2=move(other.winsp2);
    for (unsigned long i = 0; i < halfDeck; i++) {
      log[i] = move(other.log[i]);
    }
  }
  return *this;
}

Game::~Game(){
    player1.setPlaying(0);
    player2.setPlaying(0);
}

string strCardVal(int val){
    if(val==14) return "Ace";
    else if(val==11)return "Jack";
    else if(val==12)return "Queen";
    else if(val==13)return "King";
    else return to_string(val);
}

void Game::playTurn(){
    if(stack1.empty()){
        if(player1.cardesTaken()+player2.cardesTaken()<fullDeck){
            int cardsDown=fullDeck-(player1.cardesTaken()+player2.cardesTaken());
            player1.setCardsTaken(player1.cardesTaken()+(cardsDown/2));
            player2.setCardsTaken(player2.cardesTaken()+(cardsDown/2));
        }
        throw "no more turns to play. game is over.";
    }
    Card c1=stack1.top();
    stack1.pop();
    Card c2=stack2.top();
    stack2.pop();
    int cardVal1=c1.getValue();
    int cardVal2=c2.getValue();
    if((cardVal1>cardVal2 && (cardVal1!=14 && cardVal2!=2)) || (cardVal1==2 && cardVal2==14)){
        string log= player1.getName()+" played "+strCardVal(cardVal1)+" of "+c1.getType()+" "+
            player2.getName()+" played "+strCardVal(cardVal2)+" of "+c2.getType()+". "+
            player1.getName()+" wins.";
        this->log[(unsigned long)roundNum]=log;
        roundNum++; 
        player1.setStackSize(stack1.size());
        player2.setStackSize(stack2.size());
        player1.setCardsTaken(player1.cardesTaken()+2);
        winsp1++;
    }
    else if(cardVal1<cardVal2 || (cardVal1==14 && cardVal2==2)){
        string log= player1.getName()+" played "+strCardVal(cardVal1)+" of "+c1.getType()+" "+
            player2.getName()+" played "+strCardVal(cardVal2)+" of "+c2.getType()+". "+
            player2.getName()+" wins.";
        this->log[(unsigned long)roundNum]=log;
        roundNum++;  
        player1.setStackSize(stack1.size());
        player2.setStackSize(stack2.size());
        player2.setCardsTaken(player2.cardesTaken()+2);
        winsp2++;
    }
    else{
        string log= player1.getName()+" played "+strCardVal(cardVal1)+" of "+c1.getType()+" "+
            player2.getName()+" played "+strCardVal(cardVal2)+" of "+c2.getType()+". Draw.";
        this->log[(unsigned long)roundNum]=log;
        drawNum++;
        playTurn();
    }
}

void Game::printLastTurn(){
    if(roundNum==0) throw "last turn does not exist";
    cout<<log[(unsigned long)roundNum-1]<<endl;
}

void Game::playAll(){
    if(stack1.empty()) throw "no more turns to play. game is over.";
    while (!stack1.empty()){
        playTurn();
    }
}

void Game::printWiner(){
    if(player1.cardesTaken()>player2.cardesTaken())cout<<player1.getName()<<endl;
    else if(player1.cardesTaken()<player2.cardesTaken())cout<<player2.getName()<<endl;
    else cout<< "tie game. no winner."<<endl;
}

void Game::printLog(){
    if(roundNum==0) throw "log does not exist";
    for (int i = roundNum-1; i >= 0; i--)
    {
        cout<<log[(unsigned long)i]<<endl;
    }
}

void Game::printStats(){
    double winRatep1= (double)winsp1/roundNum;
    double winRatep2= (double)winsp2/roundNum;
    double drawRate=(double)drawNum/roundNum;
    cout<<"Player 1:\nName- "<<player1.getName()<<", Win Rate= "<<winRatep1<<", Cards Won= "<<player1.cardesTaken()<<endl;
    cout<<"Player 2:\nName- "<<player2.getName()<<", Win Rate= "<<winRatep2<<", Cards Won= "<<player2.cardesTaken()<<endl;
    cout<<"Draw Rate= "<<drawRate<<", Number Of Draws= "<<drawNum<<endl;
}

