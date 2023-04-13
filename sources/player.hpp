#pragma once

#include <iostream>

namespace ariel
{
    class Player{
        std::string name;
        int stackSize;
        int cardsTaken;
        int playing;

        public:
            Player(std::string name);
            Player(const Player &other);
            Player& operator=(const Player& other);
            Player(Player&& other) noexcept;
            Player& operator=(Player&& other) noexcept;
            ~Player();
            int stacksize();
            void setStackSize(int size);
            int cardesTaken();
            void setCardsTaken(int num);
            int getPlaying();
            void setPlaying(int playing);
            std::string getName();
    };
}
 