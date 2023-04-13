#pragma once

#include <iostream>
#include <stack>
#include <array>
#include "player.hpp"
#include "card.hpp"

namespace ariel
{
    class Game{
        Player player1, player2;
        static const int fullDeck=52;
        static const int halfDeck=26;
        stack<Card> stack1, stack2;
        array<string, halfDeck> log;
        int roundNum;
        int drawNum;
        int winsp1;
        int winsp2;


        public:
        Game(Player pl1, Player pl2);
        Game(const Game &other);
        Game& operator=(const Game& other);
        Game(Game&& other) noexcept;
        Game& operator=(Game&& other) noexcept;
        ~Game();
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
    };
}