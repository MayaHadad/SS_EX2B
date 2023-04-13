#pragma once

#include <iostream>
using namespace std;

namespace ariel
{
    class Card{
        int value;
        string type;

        public:
            Card();
            Card(int val, string type);
            Card(const Card &card);
            Card& operator=(const Card& other);
            Card(Card&& other) noexcept;
            Card& operator=(Card&& other) noexcept;
            ~Card();
            int getValue();
            string getType();
    };
}
 